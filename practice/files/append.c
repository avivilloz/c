/*****************************************************************************
* title: Append to file
* author: aviv illoz
* description: Appends strings to file, and execute some commands
******************************************************************************/

#include <stdio.h> /* i/o and file-funcs */
#include <stdlib.h> /* malloc */
#include <string.h> /* strlen, strcmp */

#define _ARR_SIZE_ 6

static char file_name[20];
static FILE *fp = NULL;
static int counter = 1;

typedef struct actions
{
	char *cmd;
	int (*func_cmp)(const char *cmd, const char *str);
	int (*func_op)();
} actions_t;

enum return_status
{
	EXIT = -1,
	SUCCESS,
	FAILURE
};

int Exit(void);
int RemoveFile(void);
int CloseFile(void);
int CountLines(void);
int AppendLines(void);
int OpenFile(void);
int AnalizeCmds(char *input);
void AskUser();

int main(void)
{
	AskUser();

	return 0;
}

void AskUser(void)
{
	char input[10];
	int check = SUCCESS;
	
	do {
		if (NULL != fp)
		{
			printf("FILE: <\"%s\">\n", file_name);
		}	
	
		printf("OPTIONS:\n-open (to open file).\n-append (to add lines).\n-count (to count lines).\n-close (to close file).\n-remove (to remove file).\n-exit (to exit program).\n\n");		

		scanf("%s", input);

		check = AnalizeCmds(input);	
	
	} while (EXIT != check);
}

int AnalizeCmds(char *input)
{
	int i = 0;
	int check = SUCCESS;

	actions_t actions_arr[_ARR_SIZE_] = {

		{"open", strcmp, OpenFile},
		{"append", strcmp, AppendLines},
		{"count", strcmp, CountLines},
		{"close", strcmp, CloseFile},
		{"remove", strcmp, RemoveFile},
		{"exit", strcmp, Exit},

	};

	for (; i < _ARR_SIZE_; i++)
	{
		if (0 == actions_arr[i].func_cmp(actions_arr[i].cmd, input))
		{
			getchar();
		
			check = actions_arr[i].func_op();
		
			break;	
		}
	}

	return check;
}

int OpenFile(void)
{	
	if (NULL == fp)
	{
		printf("\nEnter file name: "); 

		scanf("%s", file_name);

		fp = fopen(file_name, "a+");

		printf("\n");

  		if (fp == NULL) 
		{ 
        		printf("COULD NOT OPEN FILE\n\n"); 

       			return FAILURE; 
    		}

		printf("FILE \"%s\" OPENED\n\n", file_name);

		return SUCCESS;
	}

	printf("\nFILE \"%s\" STILL OPENED\n\n", file_name);

	return FAILURE;
}

int AppendLines(void)
{	
	char key = '\0';
	char str[200];
	char **buffer = NULL;
	char c = '\0';
	int i = 0, lines = 0;
	unsigned int j = 0;

	if (NULL == fp)
	{
		printf("\nNO FILE OPENED\n\n");	

		return FAILURE;
	}

	while ('n' != key && 'N' != key)
	{

		printf("\nWould you like to append a line to your file? (Y/N)\n");

		system("stty -icanon -echo");

		scanf("%c", &key);

		if ('y' == key || 'Y' == key)
		{
			system("stty icanon echo");

			printf("Add new line:\n\n%d- ", counter); 

			++counter; 

			c = fgetc(stdin);       

   			fgets(str, 200, stdin);

			printf("\n");

			if ('<' == c)
			{
				fseek(fp, 0, SEEK_SET);

				for (lines = 0, c = fgetc(fp); c != EOF; c = getc(fp)) 	
				{
        				if (c == '\n') 
					{
        					++lines;
					}
				}

				buffer = (char**) malloc(lines * sizeof(char*));

				fseek(fp, 0, SEEK_SET);

				for (i = 0; i < lines; i++)
				{
					for (j = 0, c = fgetc(fp); '\n' != c; c = fgetc(fp), j++)
					{}
			
					buffer[i] = (char *) malloc((j + 2) * sizeof(char));
				}

				fseek(fp, 0, SEEK_SET);

				for (i = 0; i < lines; i++)
				{
					for (j = 0, c = fgetc(fp); '\n' != c; c = fgetc(fp), j++)
					{
						buffer[i][j] = c;
					}

					buffer[i][j] = '\n';
					buffer[i][j+1] = '\0';
				}
		
				fclose(fp);			
		
				fp = fopen(file_name, "w+");
			
				fputs(str, fp);

				fclose(fp);

				fp = fopen(file_name, "a+");

				for (i = 0; i < lines; i++)
				{
					for (j = 0; strlen(buffer[i]) != j; j++)
					{
						fputc(buffer[i][j], fp);
					}
				}

				for (i = 0; i < lines; i++)
				{
					free(buffer[i]);
				}

				free(buffer);

				buffer = NULL;
			}	
			else
			{
				fputc(c, fp);
		
				fputs(str, fp);
			}	
		}
	}

	system("stty icanon echo");

	return SUCCESS;
}

int CountLines(void)
{
	int lines = 0;
	char c;

	if (NULL == fp)
	{
		printf("\nNO FILE OPENED\n\n");
		
		return FAILURE;
	}

	fseek(fp, 0, SEEK_SET);

	for (c = fgetc(fp); c != EOF; c = getc(fp)) 	
	{
        	if (c == '\n') 
		{
        		++lines;
		}
	}
	
	printf("\nLINES: %d\n\n", lines);

	return SUCCESS;
}

int CloseFile(void)
{
	if (NULL == fp)
	{
		printf("\nNO FILE OPENED\n\n");	

		return FAILURE;
	}
	
	fclose(fp);
	
	fp = NULL;

	counter = 1;

	printf("\nFILE \"%s\" CLOSED\n\n", file_name);	
	
	return SUCCESS;
}

int RemoveFile(void)
{
	if (NULL != fp)
	{
		int check = 0;

		check = remove(file_name);

		if (-1 == check)
		{
			printf("\nCOULDN'T REMOVE FILE\n\n");

			return FAILURE;
		}

		CloseFile();

		printf("\nFILE \"%s\" REMOVED\n\n", file_name);

		return SUCCESS; 
	}

	printf("\nNO FILE TO REMOVE\n\n");

	return FAILURE;
}

int Exit(void)
{
	printf("\nBYE!\n\n");

	if (NULL != fp)
	{
		fclose(fp);

		fp = NULL;
	}
	
	return EXIT;
}
