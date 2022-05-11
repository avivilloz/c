/*****************************************************************************
* title:Boom7
* author: aviv illoz
* description: Prints BOOM whenever there is a 7 in a number, or if the number 
* is divisible by 7
******************************************************************************/

#include <stdio.h> /* printf */

void Boom(int curr_num, int dest)
{	 	
	for (; curr_num <= dest; curr_num++)
	{
		int i = 0, check = 0;
		int mod = 1, new_digit = 0;

		while (curr_num >= mod || (curr_num * -1) >= mod)
		{
			mod *= 10;	
			i++;
		}
		
		for (; i > 0; i--)
		{
			new_digit = ((curr_num % mod) / (mod / 10));
		
			if (7 == new_digit && 0 == check)
			{
				printf("BOOM\n");
				check = 1;
			}

			mod /= 10;
		}

		if (curr_num % 7 == 0 && 0 == check)
		{
			printf("BOOM\n");
		}

		else if (0 == check)
		{
			printf("%d\n", curr_num); 
		}
	}
}

int main(void)
{
	Boom(5, 1000);

	return 0;
}
