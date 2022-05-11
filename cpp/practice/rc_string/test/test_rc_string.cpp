/*****************************************************************************
Title: rc_string - Infinity Labs R&D 
Group: OL91
Author: Aviv
Description: rc_string test
******************************************************************************/

#include <iostream> // cout

#include "rc_string.hpp" // api

using namespace std;
using namespace ilrd;

#define TEST(is_good, msg) if (0 == is_good) {cout << msg << ": fail\n";}

/*****************************************************************************/

int main()
{
    RCString s1("hello");
    cout << s1 << endl;
    RCString s2("aviv");
    cout << s2 << endl;
    RCString s3(s1);

    TEST((s1 > s2), ">");
    TEST((s2 < s1), "<");
    
    TEST((s1 == s3), "==");

    s1 = s2;
    TEST((s1 == s2), "==");

    s1[0] = 'b';
    TEST((s1 == "bviv"), "[]");

    cout << s1 << " - index 2: " << s1[2] << endl;

    return 0;
}

/*****************************************************************************/

