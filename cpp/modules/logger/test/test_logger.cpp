/*****************************************************************************
Title: logger - Infinity Labs R&D 
Group: OL91
Author: Aviv
Description: logger test
******************************************************************************/

#include <iostream> // cout

#include "logger.hpp" // api

using namespace std;
using namespace ilrd;

/*****************************************************************************/

int main()
{
    Logger *l = Singleton<Logger>::GetInstance();

    string s("hey my name is aviv\n");

    l->Log(s);
    l->Log(s);
    l->Log(s);
    l->Log(s);
    l->Log(s);
    l->Log(s);
    l->Log(s);

    sleep(2);

    return 0;
}

/*****************************************************************************/
