/*****************************************************************************
Title: simple_string - Infinity Labs R&D 
Group: OL91
Author: Aviv
Description: simple_string test
******************************************************************************/

#include <iostream> // cout
#include <ctime> // clock

#include "simple_string.hpp" // api

using namespace std;

/*****************************************************************************/

int main()
{
    String s1("hello");
    cout << "s1: " << s1.CStr() << endl;
    cout << "lenght of s1 is: " << s1.Length() << endl;

    String s2 = s1;
    cout << "s2: " << s2.CStr() << endl;
    cout << "lenght of s2 is: " << s2.Length() << endl;

    String s3(s2);
    cout << "s3: " << s3.CStr() << endl;
    cout << "lenght of s3 is: " << s3.Length() << endl;

///////////////////////////////////////////////////////////////////////////////
    s2 = s2;
    cout << "s2: " << s2.CStr() << endl;
    cout << "lenght of s2 is: " << s2.Length() << endl;

    String s4 = "how are you?";

    s2 = s4;
    cout << "s2: " << s2.CStr() << endl;
    cout << "lenght of s2 is: " << s2.Length() << endl;
///////////////////////////////////////////////////////////////////////////////
    if (s1 == s3)
    {
        cout << "s1 == s3: " << "true" << endl;
    }
    else
    {
        cout << "s1 == s3: " << "false" << endl;
    }

    if (s1 == s2)
    {
        cout << "s1 == s2: " << "true" << endl;
    }
    else
    {
        cout << "s1 == s2: " << "false" << endl;
    }

    if (s1 == "hello")
    {
        cout << "s1 == hello: " << "true" << endl;
    }
    else
    {
        cout << "s1 == hello: " << "false" << endl;
    }
///////////////////////////////////////////////////////////////////////////////
    if (s1 > s2)
    {
        cout << "s1 > s3: " << "true" << endl;
    }
    else
    {
        cout << "s1 > s3: " << "false" << endl;
    }

    if (s1 > "hello")
    {
        cout << "s1 > hello: " << "true" << endl;
    }
    else
    {
        cout << "s1 > hello: " << "false" << endl;
    }
///////////////////////////////////////////////////////////////////////////////
    if (s1 < s2)
    {
        cout << "s1 < s3: " << "true" << endl;
    }
    else
    {
        cout << "s1 < s3: " << "false" << endl;
    }

    if (s1 < "hello")
    {
        cout << "s1 < hello: " << "true" << endl;
    }
    else
    {
        cout << "s1 < hello: " << "false" << endl;
    }
///////////////////////////////////////////////////////////////////////////////
    if (s1 >= s2)
    {
        cout << "s1 >= s3: " << "true" << endl;
    }
    else
    {
        cout << "s1 >= s3: " << "false" << endl;
    }

    if (s1 >= "hello")
    {
        cout << "s1 >= hello: " << "true" << endl;
    }
    else
    {
        cout << "s1 >= hello: " << "false" << endl;
    }
///////////////////////////////////////////////////////////////////////////////
    if (s1 <= s2)
    {
        cout << "s1 <= s3: " << "true" << endl;
    }
    else
    {
        cout << "s1 <= s3: " << "false" << endl;
    }

    if (s1 <= "hello")
    {
        cout << "s1 <= hello: " << "true" << endl;
    }
    else
    {
        cout << "s1 <= hello: " << "false" << endl;
    }
///////////////////////////////////////////////////////////////////////////////

    cout << s2 << endl;

    clock_t start = clock();
    for (std::size_t i = 0; i < 5000000; ++i)
    {
        "1234" == s1;
    } 
    clock_t end = clock();

    cout << "time: " << end - start << endl;

    return 0;
}

/*****************************************************************************/

