/*****************************************************************************
Title: rand 
Description: learn rand
******************************************************************************/

#include <stdio.h> /* printf */
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/*****************************************************************************/

int GetNumOfIterations(int highest_num, int num_in_range)
{
    int temp = -1;
    size_t i = 0;

	srand(time(NULL));

    while (num_in_range != temp)
    {
        temp = rand() % highest_num;
        ++i;
    }

    return i;
}

int main(void)
{
	size_t i = 0;
	int values = 0;
	for (; i < 100; ++i)
	{
		values += GetNumOfIterations(100, 7);
		sleep(1);
	}
	printf("avarage: %d/n", values / 100);

	return 0;
}

/*****************************************************************************/

