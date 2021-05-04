/*****************************************************************************
Title: ext2
Author: Aviv
Description: ext2 API
******************************************************************************/

#include <stdio.h> /* printf, fputs, puts, perror */
#include <stdlib.h> /* exit */
#include <string.h> /* strcmp, strtok */
#include <unistd.h> /* lseek, read, close */
#include <fcntl.h> /* open */
#include <sys/stat.h> /* S_ISDIR */

#include "ext2_fs.h"
#include "ext2.h" /* api */

/*****************************************************************************/

static void ExitIfBad(int is_good)
{
	if (!is_good)
	{
		perror("error");
		exit(1);
	}
}

static void MsgIfBad(int is_good, const char *msg)
{
	if (!is_good)
	{
		fprintf(stderr, msg, "\n");
		exit(1);
	}
}

/*****************************************************************************/

#define BASE_OFFSET 1024
#define SB_STRUCT_SIZE sizeof(struct ext2_super_block)
#define GD_STRUCT_SIZE sizeof(struct ext2_group_desc)
#define INODE_STRUCT_SIZE sizeof(struct ext2_inode)
#define BLOCK_OFFSET(block) (block * g_block_size)
#define GROUP_NUM(inode_num) (inode_num / g_inodes_per_group)
#define INODE_NUM(inode_num) (inode_num % g_inodes_per_group)

static unsigned int g_block_size = 0; 
static unsigned int g_inode_size = 0;
static unsigned int g_inodes_per_group = 0;

static int GetInodeOffset(const struct ext2_group_desc *gd, int inode_num)
{
	return BLOCK_OFFSET(gd->bg_inode_table) + ((inode_num - 1) * g_inode_size);
}

static int GetGDOffset(int group_num)
{
	return g_block_size + (group_num * GD_STRUCT_SIZE);
}

/*****************************************************************************/

static void GetSuperBlock(int fd, struct ext2_super_block *_sb);
static void GetGroupDescriptor(int fd, int group_num, struct ext2_group_desc *_gd);
static void GetInode(
	int fd, int inode_num, 
	const struct ext2_group_desc *gd, 
	struct ext2_inode *_inode	
);
static void GetBlock(int fd, int block_num, void *_block);
static void PrintSuperBlock(const struct ext2_super_block *sb);
static void PrintGroupDescriptor(const struct ext2_group_desc *gd);
static void PrintInode(const struct ext2_inode *inode);
static void PrintFileContent(int fd, const struct ext2_inode *inode);

/*****************************************************************************/

void PrintFileInfo(const char *device_path, const char *file_path)
{
	size_t size = 0;
	int fd = 0;
	char *file_path_buff = NULL;
	char *token = NULL;
	void *block = NULL;
	struct ext2_super_block sb;
	struct ext2_group_desc gd;
	struct ext2_inode inode;
	struct ext2_dir_entry *entry = NULL;

	fd = open(device_path, O_RDONLY);
	ExitIfBad(-1 != fd);

	GetSuperBlock(fd, &sb); 
	g_block_size = BASE_OFFSET << sb.s_log_block_size;
	g_inode_size = sb.s_inode_size;
	g_inodes_per_group = sb.s_inodes_per_group;

	GetGroupDescriptor(fd, 0, &gd);
	GetInode(fd, 2, &gd, &inode); /* getting root */

	/* creating buffer for strtok */
	file_path_buff = (char *)malloc(strlen(file_path) + 1); 
	ExitIfBad(NULL != file_path_buff);
	strcpy(file_path_buff, file_path);

	block = malloc(g_block_size);
	ExitIfBad(NULL != block); 

	for (token = strtok(file_path_buff, "/"); 
		 NULL != token; token = strtok(NULL, "/"))
	{
		size = 0;

		GetBlock(fd, inode.i_block[0], block);
		entry = (struct ext2_dir_entry *)block;
		
		while (0 != strncmp(token, entry->name, entry->name_len))
		{
			size += entry->rec_len;
			entry = (struct ext2_dir_entry *)((char *)entry + entry->rec_len);
			MsgIfBad((size < inode.i_size) && 0 != entry->inode, 
						"error: file not found");
		}

		GetGroupDescriptor(fd, GROUP_NUM(entry->inode), &gd);
		GetInode(fd, INODE_NUM(entry->inode), &gd, &inode);
	}

	MsgIfBad(0 == S_ISDIR(inode.i_mode), "error: path refers to a directory");

	puts("");
	PrintSuperBlock(&sb);	
	puts("");
	PrintGroupDescriptor(&gd);
	puts("");
	PrintInode(&inode);
	puts("");
	PrintFileContent(fd, &inode);
	puts("");

	free(file_path_buff);
	file_path_buff = NULL;	

	free(block);
	block = NULL;

	ExitIfBad(-1 != close(fd));
}

static void GetSuperBlock(int fd, struct ext2_super_block *_sb)
{
	ExitIfBad(-1 != lseek(fd, BASE_OFFSET, SEEK_SET));
	ExitIfBad(-1 != read(fd, _sb, SB_STRUCT_SIZE));
	MsgIfBad(EXT2_SUPER_MAGIC == _sb->s_magic, "error: not an ext2 file system");
}

static void GetGroupDescriptor(int fd, int group_num, struct ext2_group_desc *_gd)
{
	ExitIfBad(-1 != lseek(fd, GetGDOffset(group_num), SEEK_SET));
	ExitIfBad(-1 != read(fd, _gd, sizeof(struct ext2_group_desc)));
}

static void GetInode(
	int fd, int inode_num, 
	const struct ext2_group_desc *gd, 
	struct ext2_inode *_inode	
)
{
	ExitIfBad(-1 != lseek(fd, GetInodeOffset(gd, inode_num), SEEK_SET));
	ExitIfBad(-1 != read(fd, _inode, INODE_STRUCT_SIZE));
}

static void GetBlock(int fd, int block_num, void *_block)
{
	ExitIfBad(-1 != lseek(fd, BLOCK_OFFSET(block_num), SEEK_SET));
	ExitIfBad(-1 != read(fd, _block, g_block_size));
}

static void PrintSuperBlock(const struct ext2_super_block *sb)
{
	printf("READING SUPERBLOCK:\n"
		   "Inodes count            : %u\n"
		   "Blocks count            : %u\n"
		   "Reserved blocks count   : %u\n"
		   "Free blocks count       : %u\n"
		   "Free inodes count       : %u\n"
		   "First data block        : %u\n"
		   "Block size              : %u\n"
		   "Blocks per group        : %u\n"
		   "Inodes per group        : %u\n"
		   "Creator OS              : %u\n"
		   "First non-reserved inode: %u\n"
		   "Size of inode structure : %hu\n"
		   ,
		   sb->s_inodes_count,
		   sb->s_blocks_count,
		   sb->s_r_blocks_count,     
		   sb->s_free_blocks_count,
		   sb->s_free_inodes_count,
		   sb->s_first_data_block,
		   g_block_size,
		   sb->s_blocks_per_group,
		   sb->s_inodes_per_group,
		   sb->s_creator_os,
		   sb->s_first_ino,         
		   sb->s_inode_size);
}

static void PrintGroupDescriptor(const struct ext2_group_desc *gd)
{
	printf("READING GROUP DESCRIPTOR:\n"
	       "Blocks bitmap block: %u\n"
	       "Inodes bitmap block: %u\n"
	       "Inodes table block : %u\n"
	       "Free blocks count  : %u\n"
	       "Free inodes count  : %u\n"
	       "Directories count  : %u\n"
	       ,
	       gd->bg_block_bitmap,
	       gd->bg_inode_bitmap,
	       gd->bg_inode_table,
	       gd->bg_free_blocks_count,
	       gd->bg_free_inodes_count,
	       gd->bg_used_dirs_count); 
}

static void PrintInode(const struct ext2_inode *inode)
{
	size_t i = 0;

	printf("READING INODE:\n"
	       "File mode: %hu\n"
	       "Owner UID: %hu\n"
	       "Size     : %u bytes\n"
	       "Blocks   : %u\n"
	       ,
	       inode->i_mode,
	       inode->i_uid,
	       inode->i_size,
	       inode->i_blocks);

	for(; i < EXT2_N_BLOCKS; i++)
	{
		if (i < EXT2_NDIR_BLOCKS)  
		{
			printf("Block %lu : %u\n", i, inode->i_block[i]);
		}
		else if (i == EXT2_IND_BLOCK)
		{
			printf("Single   : %u\n", inode->i_block[i]);
		}
		else if (i == EXT2_DIND_BLOCK) 
		{
			printf("Double   : %u\n", inode->i_block[i]);
		}
		else if (i == EXT2_TIND_BLOCK)
		{
			printf("Triple   : %u\n", inode->i_block[i]);
		}
	}
}

static void PrintFileContent(int fd, const struct ext2_inode *inode)
{
	size_t i = 0;
	char *buffer = (char *)malloc(g_block_size);
	ExitIfBad(NULL != buffer);

	puts("READING FILE CONTENT:");

	for(; i < EXT2_N_BLOCKS; i++)
	{
		if (i < EXT2_NDIR_BLOCKS)    
		{
			ExitIfBad(-1 != lseek(fd, BLOCK_OFFSET(inode->i_block[i]), SEEK_SET));
			ExitIfBad(-1 != read(fd, buffer, g_block_size)); 
			printf("%s", buffer);
		}
		else if (i == EXT2_IND_BLOCK) 
		{
			printf("Single   : %u\n", inode->i_block[i]);
		}
		else if (i == EXT2_DIND_BLOCK) 
		{
			printf("Double   : %u\n", inode->i_block[i]);
		}
		else if (i == EXT2_TIND_BLOCK) 
		{
			printf("Triple   : %u\n", inode->i_block[i]);
		}
	}

	free(buffer);
	buffer = NULL;
}

/*****************************************************************************/
