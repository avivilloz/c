/*****************************************************************************
Title: simple_bit_array - Infinity Labs R&D 
Group: OL91
Author: Aviv
Description: simple_bit_array test
******************************************************************************/

#include <iostream> // cout

#include "simple_bit_array.hpp" // api

using namespace std;
using namespace ilrd;

/*****************************************************************************/

int main()
{
    BitArray ba1;
    BitArray ba2;

    ba1[3] = 1;
    ba1[7] = 1;
    ba1[28] = 1;

    ba2 = ba1;

    for (size_t i = 0; i < 64; ++i)
    {
        cout << ba2[i] << endl;
    }

    if (ba1[3])
    {
        cout << "i'm true" << endl;
    }

    if (ba1[2])
    {
        cout << "i'm false" << endl;
    }

    BitArray ba3;

    ba3[3] = ba1[3];

    cout << ba1[3] << endl;
    cout << ba3[3] << endl;

    return 0;
}

/*****************************************************************************/

