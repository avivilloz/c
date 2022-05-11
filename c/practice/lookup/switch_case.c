/*****************************************************************************
* title: Lut 1
* author: aviv illoz
* description: Prints A pressed or T pressed if you press the corresponding 
* keys (using switch/case)
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
		
		switch (key)
		{
		case __A__:
			printf("A pressed\n");
			break;
		case __T__: 
			printf("T pressed\n");
			break;
		}

	} while (__ESC__ != key);

	system("stty icanon echo");

	return 0;
}
