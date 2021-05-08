#include <stdio.h>

void TF(int num)
{
	int i = 1;

	for (; i <= num; i++)
	{
		if (i % 3 == 0)
		{
			printf("T");
		}
		if (i % 5 == 0)
		{
			printf("F");
		}
		if (i % 3 != 0 && i % 5 != 0)
		{
			printf("%d", i);
		}
		printf("\n");
	}
}

int main(void)
{
	TF(30);

	return 0;
}
