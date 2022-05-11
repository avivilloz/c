/*****************************************************************************
Title: composite - Infinity Labs R&D 
Group: OL91
Author: Aviv
Description: composite test
******************************************************************************/

#include "tree.hpp" // api

using namespace ilrd;

/*****************************************************************************/

int main(int argc, char *argv[]) 
{
    Tree t(argv[1]);
    t.Print();

    (void)argc;
    
    return 0;
}

/*****************************************************************************/

