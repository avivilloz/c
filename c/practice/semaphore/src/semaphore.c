/*****************************************************************************
Title: Semaphore
Author: Aviv Illoz
Description: Semaphore api
******************************************************************************/

#include <stdio.h>		/* printf, fgets */
#include <stdlib.h>		/* atoi */
#include <sys/sem.h>	/* semaphore funcs */
#include <unistd.h>		/* access */
#include <string.h>		/* strcpy, strcat, strcmp */
#include <errno.h>		/* errno */

/*****************************************************************************/

#define SEM_INITIAL_VAL 10
#define NUM_OF_OPTIONS 4
#define PATH_LENGTH 70
#define INPUT_LENGTH 30
#define POSSIBLE_NUM_OF_ARGS 3

enum {FALSE = 0, TRUE}; 
enum {SUCCESS = 0, FAILURE};
enum {CONTINUE = 0, EXIT};

/*****************************************************************************/

typedef struct option
{
	char cmd;
	char *instruction;
	int (*action)(const char *input, int semid);
} option_t;

union semun 
{
    int val;	/* used for SETVAL only */
};

/************************* FUNCTION DECLARATIONS *****************************/

static int SemCreate(char *name, int *semid);
static int SemDestroy(int semid);

/***************************************/

static void InitOptions(option_t options[NUM_OF_OPTIONS]);
static void Logger(int semid, const option_t options[NUM_OF_OPTIONS]);
static int AnalizeCmds(
	const char *input, 
	int semid, 
	const option_t options[NUM_OF_OPTIONS]
);

/***************************************/

static int SemControl(const char *input, int semid);
static int SemGetValue(const char *ignored, int semid);
static int SemExit(const char *ignored, int unused);

/******************************** HELPER *************************************/

static int FileExists(char *path)
{
	if (-1 == access(path, F_OK)) 
	{
		return FALSE;
	} 

	return TRUE;
}

static int Lex(const char *input, char *args[])
{
	int counter = 0;
	char *curr = (char *)input;
	char *token = NULL;

	for (; ; ++counter, curr = NULL)
	{
		token = strtok(curr, " ");
		if (NULL == token)
		{
			break;
		}
		args[counter] = token;
	}

	return counter;
}

/*****************************************************************************/

int main(int argc, char *argv[])
{
	int semid = 0;
	option_t options[NUM_OF_OPTIONS];

	if (1 == argc)
	{		
		fputs("semaphore's name not provided\n", stderr);
		return FAILURE;
	}

	if (FAILURE == SemCreate(argv[1], &semid))
	{
		return FAILURE;
	}

	InitOptions(options);

	Logger(semid, options);

	return SUCCESS;
}

/******************************** FUNCTIONS **********************************/

static int SemCreate(char *name, int *semid)
{
	FILE *fp = NULL;
	key_t key = 0;
	char path[PATH_LENGTH];
	int file_existed = 1;

	strcpy(path, "./keys/");
	strcat(path, name);

	if (!FileExists(path))
	{
		if (ENOENT == errno)
		{
			fp = fopen(path, "a+");
			if (NULL == fp)
			{
				perror("Error: ");
				fputs("failed to create file for key\n", stderr);
				return FAILURE;			
			}
			fclose(fp);

			file_existed = 0;
		}
		else
		{
			perror("Error: ");
			fputs("failed to access file for key\n", stderr);
			return FAILURE;
		}
	}

	key = ftok(path, 'a');
	if (-1 == key)
	{
		perror("Error: ");
		fputs("failed to create key\n", stderr);
		return FAILURE;
	}

	if (!file_existed)
	{
		union semun param;

		*semid = semget(key, 1, 0777 | IPC_CREAT);
		if (-1 == *semid)
		{
			perror("Error: ");
			fputs("failed to create semaphore\n", stderr);
			return FAILURE;
		}

		param.val = SEM_INITIAL_VAL;
		if (-1 == semctl(*semid, 0, SETVAL, param))
		{
			perror("Error: ");
			fputs("failed to initialize semaphore\n", stderr);
			return SemDestroy(*semid);
		}

		fputs("\nsucceeded to create semaphore\n", stdout);
	}
	else
	{
		*semid = semget(key, 1, 0);
		if (-1 == *semid)
		{
			perror("Error: ");
			fputs("failed to get semaphore's id\n", stderr);
			return FAILURE;
		}
		
		fputs("\nsucceeded to open semaphore\n", stdout);
	}
	
	
	return SUCCESS;
}

static int SemDestroy(int semid)
{	
	if (-1 == semctl(semid, 0, IPC_RMID))
	{
		perror("Error: ");
		fputs("failed to destroy semaphore\n", stderr);
		return FAILURE;
	}

	fputs("semaphore destroyed\n", stdout);

	return FAILURE;
}

static void InitOptions(option_t options[])
{
	options[0].cmd = 'D';
	options[0].instruction = "D number [undo] - to decrease number";
	options[0].action = SemControl;
	
	options[1].cmd = 'I';
	options[1].instruction = "I number [undo] - to increase number";
	options[1].action = SemControl;

	options[2].cmd = 'V';
	options[2].instruction = "V               - to get value";
	options[2].action = SemGetValue;

	options[3].cmd = 'X';
	options[3].instruction = "X               - to exit";
	options[3].action = SemExit;
}

static void Logger(int semid, const option_t options[NUM_OF_OPTIONS])
{
	char input[INPUT_LENGTH];
	size_t i = 0;

	do {
		printf("\n---------------------------------------------\n\noptions:\n");
		for (i = 0; i < NUM_OF_OPTIONS; ++i)
		{
			printf("%lu-  %s\n", i + 1, options[i].instruction);
		}
		printf("\n---------------------------------------------\n\n--> ");
		if (NULL == fgets(input, INPUT_LENGTH, stdin))
		{
			fputs("failed to receive input\n", stderr);
			continue;
		}
		/* adding null character in the end */
		input[strcspn(input, "\n")] = '\0';
	} while (EXIT != AnalizeCmds(input, semid, options));
}

static int AnalizeCmds(
	const char *input, 
	int semid, 
	const option_t options[NUM_OF_OPTIONS]
)
{
	int check = 0;
	size_t i = 0;

	for (; i < NUM_OF_OPTIONS; ++i)
	{
		if (*input == options[i].cmd)
		{
			check = options[i].action(input, semid);
		}
	}

	return check;
}

static int SemControl(const char *input, int semid)
{
	char *args[POSSIBLE_NUM_OF_ARGS];
	int check = Lex(input, args);
	struct sembuf buffer;

	buffer.sem_flg = IPC_NOWAIT;

	/* check if undo */
	if (3 == check && 0 == strcmp(args[2], "undo"))
	{
		buffer.sem_flg = SEM_UNDO;
	}
	/* check if is valid input */
	else if (2 != check)
	{
		fputs("invalid input\n", stderr);
		return CONTINUE;
	}

	buffer.sem_num = 0;
	buffer.sem_op = atoi(args[1]);

	/* check if decrements */
	if ('D' == *args[0])
	{
		buffer.sem_op = 0 - buffer.sem_op;
	}

	if (-1 == semop(semid, &buffer, 1))
	{
		perror("Error: ");
		fputs("failed to change semaphore's value\n", stderr);
		return CONTINUE;
	}

	fputs("succeded to change semaphore's value\n", stdout);

	return CONTINUE;
}

static int SemGetValue(const char *ignored, int semid)
{
	int value = semctl(semid, 0, GETVAL);

	(void)ignored;

	if (-1 == value)
	{
		perror("Error: ");
		fputs("failed to get value\n", stderr);
	}
	else
	{
		printf("semaphore's value: %d\n", value);
	}

	return CONTINUE;
}

static int SemExit(const char *ignored, int unused)
{
	(void)ignored;
	(void)unused;

	fputs("bye\n", stdout);

	return EXIT;
}

/*****************************************************************************/
