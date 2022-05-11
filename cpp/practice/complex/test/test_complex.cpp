/*****************************************************************************
Title: complex - Infinity Labs R&D 
Group: OL91
Author: Aviv
Description: complex test
******************************************************************************/

#include <iostream> // cout

#include "complex.hpp" // api

using namespace std;
using namespace ilrd;

/*****************************************************************************/

static int IsGood(const Complex& cnum, double real, double imaginary)
{
    return (cnum.GetReal() == real) && (cnum.GetImaginary() == imaginary);   
} 

static inline int Expect(int is_good, const char *test)
{
    if (!is_good)
    {
        cout << test << " fail" << endl;
        return 1;
    }

    cout << test << " pass" << endl;
    return 0;
}

/*****************************************************************************/

int main()
{
    Complex c1(3,4);
    Complex c2(1,1);

    Expect(IsGood(c1 + c2, 4, 5), "c1 + c2");
    c1 += c2;
    Expect(IsGood(c1, 4, 5), "c1 += c2");

    Expect(IsGood(c1 - c2, 3, 4), "c1 - c2");
    c1 -= c2;
    Expect(IsGood(c1, 3, 4), "c1 -= c2");

    c2 += c1; // just to make multiplication and division testable

    //c2: real = 4, imaginary = 5
    //3*4 - 4*5 = -8
    //3*5 + 4*4 = 31

    Expect(IsGood(c1 * c2, -8, 31), "c1 * c2");
    c1 *= c2;
    Expect(IsGood(c1, -8, 31), "c1 *= c2");

    Expect(IsGood(c1 / c2, 3, 4), "c1 / c2");
    c1 /= c2;
    Expect(IsGood(c1, 3, 4), "c1 /= c2");

    cin >> c1;
    cout << c1;

    return 0;
}

/*****************************************************************************/
