/*****************************************************************************
Title: bit_array - Infinity Labs R&D 
Group: OL91
Author: Aviv
Description: bit_array test
******************************************************************************/

#include <iostream> // cout

#include "bit_array.hpp" // api

using namespace std;
using namespace ilrd;

#define EXPECT(is_good, msg) if (0 == is_good) {cout << msg << endl; return 1;}

/*****************************************************************************/

static int TestLogicalOperators()
{
    /* or | */
    BitArray<150> b1;
    BitArray<150> b2;

    b1[3] = 1;
    b1[24] = 1;
    b1[68] = 1;
    b1[121] = 1;

    b2 |= b1;

    EXPECT((0 == b2[2]), "error: OR");
    EXPECT((1 == b2[3]), "error: OR");
    EXPECT((1 == b2[24]), "error: OR");
    EXPECT((1 == b2[68]), "error: OR");
    EXPECT((1 == b2[121]), "error: OR");
    EXPECT((0 == b2[122]), "error: OR");

    /* and & */
    BitArray<150> b3;
    BitArray<150> b4;

    b3[3] = 1;
    b3[24] = 1;
    b3[68] = 1;
    b3[121] = 1;

    b4[3] = 1;
    b4[68] = 1;

    b3 &= b4;

    EXPECT((1 == b3[3]), "error: AND");
    EXPECT((0 == b3[24]), "error: AND");
    EXPECT((1 == b3[68]), "error: AND");
    EXPECT((0 == b3[121]), "error: AND");

    /* xor ^ */
    BitArray<150> b5;
    BitArray<150> b6;

    b5[3] = 1;
    b5[24] = 1;
    b5[68] = 1;
    b5[121] = 1;

    b6[3] = 1;
    b6[68] = 1;

    b5 ^= b6;

    EXPECT((0 == b5[3]), "error: XOR");
    EXPECT((1 == b5[24]), "error: XOR");
    EXPECT((0 == b5[68]), "error: XOR");
    EXPECT((1 == b5[121]), "error: XOR");

    return 0;    
}

static int TestSetAndFlip()
{
    /* SetAll */
    BitArray<150> b1;

    b1.SetAll(1);

    for (size_t i = 0; i < 150; ++i)
    {
        EXPECT((1 == b1[i]), "error: SetAll");
    }

    b1.SetAll(0);

    for (size_t i = 0; i < 150; ++i)
    {
        EXPECT((0 == b1[i]), "error: SetAll");
    }

    /* FlipAll */
    BitArray<150> b2;

    b2.FlipAll();

    for (size_t i = 0; i < 150; ++i)
    {
        EXPECT((1 == b2[i]), "error: FlipAll");
    }

    b2.FlipAll();

    for (size_t i = 0; i < 150; ++i)
    {
        EXPECT((0 == b2[i]), "error: FlipAll");
    }

    b2[4] = 1;
    b2[23] = 1;
    b2[65] = 1;
    b2[123] = 1;

    b2.FlipAll();

    EXPECT((0 == b2[4]), "error: FlipAll");
    EXPECT((0 == b2[23]), "error: FlipAll");
    EXPECT((0 == b2[65]), "error: FlipAll");
    EXPECT((0 == b2[123]), "error: FlipAll");
    EXPECT((1 == b2[2]), "error: FlipAll");
    EXPECT((1 == b2[124]), "error: FlipAll");

    /* Flip */
    BitArray<150> b3;

    b3.Flip(0);

    EXPECT((1 == b3[0]), "error: Flip");
    for (size_t i = 1; i < 150; ++i)
    {
        EXPECT((0 == b3[i]), "error: Flip");
    }

    b3.Flip(0);

    for (size_t i = 53; i < 150; ++i)
    {
        b3.Flip(i);
    }

    for (size_t i = 0; i < 52; ++i)
    {
        EXPECT((0 == b3[i]), "error: Flip");
    }

    for (size_t i = 53; i < 150; ++i)
    {
        EXPECT((1 == b3[i]), "error: Flip");
    }

    return 0;
}

static int TestBoolianOperators()
{
    BitArray<150> b1;
    BitArray<150> b2;

    EXPECT((b1 == b2), "error: ==");
    b1.FlipAll();
    EXPECT((0 == (b1 == b2)), "error: ==");
    EXPECT((b1 != b2), "error: ==");
    b2.FlipAll();
    EXPECT((0 == (b1 != b2)), "error: ==");

    return 0;
}

static int TestCtorCCtorDtor()
{
    BitArray<150> b1;
    
    b1.FlipAll();

    BitArray<150> b2(b1);

    for (size_t i = 0; i < 150; ++i)
    {
        EXPECT((1 == b2[i]), "error: CCtor");
    }

    BitArray<150> b3;

    b3 = b2;

    for (size_t i = 0; i < 150; ++i)
    {
        EXPECT((1 == b3[i]), "error: Assign Operator");
    }

    return 0;
}

static int TestCount()
{
    BitArray<150> b1;
    
    b1[7] = 1;
    b1[39] = 1;
    b1[63] = 1;
    b1[143] = 1;

    EXPECT((4 == b1.CountSetBits()), "error: CountSetBits");

    b1.SetAll(1);

    EXPECT((150 == b1.CountSetBits()), "error: CountSetBits");

    b1.SetAll(0);

    EXPECT((0 == b1.CountSetBits()), "error: CountSetBits");

    return 0;
}

static int TestToString()
{
    char buff[151];
    buff[150] = '\0';

    for (size_t i = 0; i < 150; ++i)
    {
        buff[i] = '0';
    }

    BitArray<150> b1;
    string s(b1.ToString());
    EXPECT((s == buff), "error: ToString");

    for (size_t i = 0; i < 150; ++i)
    {
        buff[i] = '1';
    }

    b1.FlipAll();
    s = b1.ToString();
    EXPECT((s == buff), "error: ToString");

    return 0;
}  

int main()
{
    EXPECT((0 == TestLogicalOperators()), "error: LOGICAL OPERATORS");
    EXPECT((0 == TestBoolianOperators()), "error: BOOLIAN OPERATORS");
    EXPECT((0 == TestSetAndFlip()), "error: SET AND FLIP");
    EXPECT((0 == TestCtorCCtorDtor()), "error: CTOR CCTOR DTOR");
    EXPECT((0 == TestCount()), "error: COUNT");
    EXPECT((0 == TestToString()), "error: TO STRING");

    cout << "SUCCESS" << endl;

    return 0;
}

/*****************************************************************************/

