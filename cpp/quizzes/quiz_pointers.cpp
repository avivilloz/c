/*****************************************************************************
Title: quiz_pointers 
Description: learn quiz_pointers
******************************************************************************/

#include <iostream>
#include <cstring>

using namespace std;

//1-implement the memcpy funtion. use only pointer arithmetic

void *Memcpy(void *dest, const void *src, std::size_t n)
{
    char *curr_dest = reinterpret_cast<char*>(dest);
    char *curr_src = (char*)(src);

    for (std::size_t i = 0; i < n; ++i)
    {
        *curr_dest = *curr_src;
        ++curr_dest;
        ++curr_src;
    }

    return dest;
}

//2-what does the following code do?
//int a = 7;
//int *ptr = &a;

//cout << ptr << endl;
//cout << *ptr << endl;

//*(char *)&ptr = 1;

//cout << ptr << endl;
//cout << *ptr << endl;

//->first cout << ptr << endl; should print address of a.
//->first cout << *ptr << endl; should print 7
//->second cout << ptr << endl; should print address of a with the last byte modified to 1
//->secong cout << *ptr << endl; should print random value

//3-write down your solutions on paper

//4-then run code on the machine but without cout / printf.

//5-instead of printing, use gdb to investigate what cout <<ptr and cout <<*ptr should 
//have printed

int main()
{
    int a = 7;
    int *ptr = &a;

//    cout << ptr << endl;
//    cout << *ptr << endl;

    *(char *)&ptr = 1;

//    cout << ptr << endl;
//    cout << *ptr << endl;

//    char dest[50];
//    const char *src = "hello world";

//    Memcpy(dest, src, strlen(src) + 1);

//    cout << dest << endl;	

    return 0;
}

/*****************************************************************************/
