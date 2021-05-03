#include <stdio.h>

static void HanoiTower(unsigned int n, char a, char b, char c)
{
	if (n > 0)
	{
		HanoiTower(n - 1, a, c, b);
		printf("move disk %u from rod %c to rod %c\n", n, a, c);
		HanoiTower(n - 1, b, a, c);
	}
}

int main(void)
{
	HanoiTower(3, 'A', 'B', 'C');

	return 0;
}
