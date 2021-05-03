#include <stdio.h>

int main(void)
{
	printf("short int = %ld\nunsigned short int = %ld\nint = %ld\nunsigned int = %ld\nlong int = %ld\nunsigned long int = %ld\nchar = %ld\nunsigned char = %ld\nfloat = %ld\ndouble = %ld\nlong double = %ld\n", 
		sizeof(short int),
		sizeof(unsigned short int),
		sizeof(int),
		sizeof(unsigned int),
		sizeof(long int),
		sizeof(unsigned long int),
		sizeof(char),
		sizeof(unsigned char),
		sizeof(float),
		sizeof(double),
		sizeof(long double));
	
	return 0;
}
