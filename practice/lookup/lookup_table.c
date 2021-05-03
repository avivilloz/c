/***************************************************************************** 
* title: Lut 3
* author: aviv illoz
* description: Prints A pressed or T pressed if you press the corresponding 
* keys (using array of funcs)
******************************************************************************/

#include <stdio.h>	/*for printf*/
#include <stdlib.h>	/*for system*/

#define __ESC__ 27
#define __A__ 97
#define __T__ 116
#define __ENTER__ 10

int Apressed(void)
{
	printf("A pressed\n");

	return 0;
}

int Tpressed(void)
{
	printf("T pressed\n");

	return 0;
}

int Enter(void)
{
	printf("\n");

	return 0;
}

int Esc(void)
{
	return 0;
}


int main(void)
{
	char key = '\0';
	size_t i = 0;

	typedef int (*func_type)();

	func_type func_array[256];

	system("stty -icanon -echo");

	for (; i < 256; i++)
	{
		func_array[i] = NULL;
	}

	func_array[__A__] = Apressed;
	func_array[__T__] = Tpressed;
	func_array[__ENTER__] = Enter;
	func_array[__ESC__] = Esc;

	while (__ESC__ != key) 
	{
		printf("Press A or T, or ESC if you want to exit:\n");
		key = getchar();
		func_array[(int)key]();
	}

	system("stty icanon echo");

	return 0;
}
