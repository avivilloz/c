/*****************************************************************************
* title: Array Program
* author: aviv illoz
* description: Gives the user options related to create and manipulate one 
* array
******************************************************************************/

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, realloc, system*/
#include <string.h> /* strcmp, strlen */

typedef struct 
{
	void *input;
	void (*func_print)(int);
	void (*func_add)(int, int);	
} elem_t;

typedef struct
{
	char type;
	int (*func_cmp)(char input, char type);
	void (*func_op)(int);
} type_t;

typedef struct
{
	char *cmd;
	int (*func_cmp)(const char *cmd, const char *str);
	int (*func_op)(void);
} action_t;

static int size = 1;
static elem_t *elem_array = NULL;
static int arr_size = 0;
static int *string_indexes_arr = NULL;

elem_t InitializeWithInt(int num);
elem_t InitializeWithFloat(float num);
elem_t InitializeWithString(char *str);

void InputInt(int index);
void InputFloat(int index);
void GuardIndex(int index);
void InputString(int index);
int CharCmp(char input, char type);
void AnalizeType(char key, int index);
int CreateArray(void);
void PrintInt(int index);
void PrintFloat(int index);
void PrintString(int index);
int PrintArray(void);
void AddToInt(int n, int index);
void AddToFloat(int n, int index);
void AddToString(int n, int index);
int AddToArray(void);
int ClearArray(void);
int Exit(void);
int AnalizeCmds(char *input);
void AskUser(void);

int main(void)
{
	AskUser();
	
	return 0;
}

void AskUser(void)
{
	char input[10];
	int check = 0;
	
	do {	
		printf("OPTIONS:\n-create (to create array).\n-print (to print array).\n-add (to add to array).\n-clear (to clear array and create new).\n-exit (to clear array and leave program).\n\n");		

		scanf("%s", input);

		printf("\n");

		check = AnalizeCmds(input);	
	
	} while (-1 != check);	
}

int AnalizeCmds(char *input)
{
	int i = 0;
	int check = 0;

	action_t action_arr[5] = {

		{"create", strcmp, CreateArray},
		{"print", strcmp, PrintArray},
		{"add", strcmp, AddToArray},
		{"clear", strcmp, ClearArray},
		{"exit", strcmp, Exit}

	};

	for (; i < 5; ++i)
	{
		if (0 == action_arr[i].func_cmp(action_arr[i].cmd, input))
		{ 
			getchar();

			check = action_arr[i].func_op();
		
			break;	
		}
	}

	return check;
}

int CreateArray(void)
{
	int i = 0;
	char key = '\0';

	if (NULL != elem_array)
	{
		printf("ARRAY ALREADY CREATED\n\n");

		return 0;
	}

	elem_array = malloc(sizeof(elem_t));
	string_indexes_arr = malloc(sizeof(int));

	while ('n' != key)
	{	
		printf("What kind of element would you like to add to the array?\n(I for int/F for float/S for string/N to decline)\n\n");

		system("stty -icanon -echo");

		scanf("%c", &key);
		
		if ('n' != key && ('s' == key || 'i' == key || 'f' == key))
		{	
			system("stty icanon echo");		
			
			if(size > 1)
			{
				elem_t *temp = realloc(elem_array, (size * sizeof(elem_t)));

				if (NULL == temp)
				{
					exit(0);
				} 				

    				elem_array = temp;

				temp = NULL;
			}
			
			AnalizeType(key, i);

			++size;
			++i;

			printf("\n");
		}
	}

	system("stty icanon echo");

	return 0;
}

void AnalizeType(char key, int index)
{
	int i = 0;

	type_t type_arr[3] = {

		{'s', CharCmp, InputString},
		{'i', CharCmp, InputInt},
		{'f', CharCmp, InputFloat}

	};

	for (; i < 3; ++i)
	{
		if (1 == type_arr[i].func_cmp(type_arr[i].type, key))
		{			
			type_arr[i].func_op(index);
		
			break;	
		}
	}
}

int CharCmp(char input, char type)
{
	return (input == type);
}

void InputInt(int index)
{
	int num = 0;
	
	printf("Integer desired: ");

	scanf("%d", &num);

	elem_array[index] = InitializeWithInt(num);

	getchar();
}

elem_t InitializeWithInt(int num)
{
	elem_t return_struct =
	{
		NULL,
		PrintInt,
		AddToInt
	};

	*(int *)(&return_struct.input) = num;
	
	return return_struct;
}

void InputFloat(int index)
{
	float num = 0;
	
	printf("Float desired: ");

	scanf("%f", &num);

	elem_array[index] = InitializeWithFloat(num);

	getchar();
}

elem_t InitializeWithFloat(float num)
{
	elem_t return_struct =
	{
		NULL,
		PrintFloat,
		AddToFloat
	};

	*(float *)(&return_struct.input) = num;
	
	return return_struct;
}

void GuardIndex(int index)
{
	++arr_size;
	
	if (arr_size > 1)
	{
		int *temp = realloc(string_indexes_arr, (arr_size * sizeof(int)));

		if (NULL == temp)
		{
			exit(0);
		} 				

    		string_indexes_arr = temp;

		temp = NULL;
	}
		
	string_indexes_arr[arr_size - 1] = index;	
}

void InputString(int index)
{
	int i = 0, j = 2;
	char *str = malloc(j);
	char input = '\0';

	GuardIndex(index);
	
	printf("String desired: ");

	scanf("%c", &input);
				
	for (; '\n' != input; ++i, ++j)
	{
		if (j > 2)
		{
			char* temp = realloc(str, j);

			if (NULL == temp)
			{
				exit(0);
			}
			
			str = temp;

			temp = NULL;
		}

		str[i] = input;

		scanf("%c", &input);
	}

	str[i] = '\0';

	elem_array[index] = InitializeWithString(str);

	str = NULL;
}

elem_t InitializeWithString(char *str)
{	
	elem_t return_struct = 
	{
		NULL,
		PrintString,
		AddToString
	};

	*(char **)(&return_struct.input) = str; 
	
	return return_struct;
}

int PrintArray(void)
{
	int i = 0;

	for (; i < size - 1; ++i)
	{
		elem_array[i].func_print(i);
	}

	printf("\n\n");

	return 0;
}

void PrintInt(int index)
{
	printf("%d ", *(int *)(&elem_array[index].input));
}

void PrintFloat(int index)
{
	printf("%f ", *(float *)(&elem_array[index].input));
}

void PrintString(int index)
{
	printf("%s ", *(char **)(&elem_array[index].input));
}

int AddToArray(void)
{
	int i = 0, n = 0;

	printf("Number to add: ");

	scanf("%d", &n);

	for (; i < size - 1; ++i)
	{	
		elem_array[i].func_add(n, i);
	}

	printf("\n%d ADDED\n\n", n);

	return 0;
}

void AddToInt(int n, int index)
{
	*(int *)(&elem_array[index].input) += n;
}

void AddToFloat(int n, int index)
{
	*(float *)(&elem_array[index].input) += (float)n;
}

void AddToString(int n, int index)
{
	int check = 1, i = 0;
	char new_digit = '\0';
	char *temp = NULL;
	int new_size = strlen(*(char **)(&elem_array[index].input)) + 1;
	char *point = *(char **)(&elem_array[index].input);

	while (check <= n)
	{
		check *= 10;
		++i;
	}

	for (; i > 0; --i)
	{		
		++new_size;
		
		temp = realloc(point, new_size);

		if (NULL == temp)
		{
			exit(0);
		}	

		new_digit = ((n % check) / (check / 10)) + 48;	

		temp[new_size - 2] = new_digit;
	
		temp[new_size - 1] = '\0';

		point = temp;

		temp = NULL;

		check /= 10;
	}

	*(char **)(&elem_array[index].input) = point;

	point = NULL;
}

int ClearArray(void)
{
	int i = 0;
	
	if (NULL == elem_array)
	{
		printf("NO ARRAY TO CLEAR\n\n");
		
		return 0;
	}
	
	for (; i < arr_size; ++i)
	{
		free(elem_array[string_indexes_arr[i]].input);
	}

	free(elem_array);

	free(string_indexes_arr);

	elem_array = NULL;

	string_indexes_arr = NULL;

	size = 1;

	arr_size = 0;

	printf("ARRAY CLEARED\n\n");

	return 0;
}

int Exit(void)
{
	ClearArray();
	
	return -1;
}
