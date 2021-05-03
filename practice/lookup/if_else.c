/*****************************************************************************
* title: Lut 2
* author: aviv illoz
* description: Prints A pressed or T pressed if you press the corresponding 
* keys (using if/else)
******************************************************************************/

#include <stdio.h>	/*for printf*/
#include <stdlib.h>	/*for system*/
#define __ESC__ 27
#define __A__ 97
#define __T__ 116

int main(void)
{
	char key;

	system("stty -icanon -echo");

	do {
		printf("Press A or T, or ESC if you want to exit:\n");

		scanf("%c", &key);	
		
		if (__A__ == key)
		{
			printf("A pressed\n");
		}
		else if (__T__ == key)
		{
			printf("T pressed\n");
		}

	} while (__ESC__ != key);

	system("stty icanon echo");

	return 0;
}
