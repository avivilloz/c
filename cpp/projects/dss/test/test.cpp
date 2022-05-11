/*****************************************************************************
Title: framework - Infinity Labs R&D 
Group: OL91
Author: Aviv
Description: framework test
******************************************************************************/

#include "framework.hpp" // api
#include "handleton.hpp" // Handleton

using namespace std;
using namespace ilrd;

/*****************************************************************************/

//extern template class ilrd::Singleton<Framework>;

int main()
{
    Handleton<Framework> framework;

    while (1)
    {}

    (void)framework;

    return 0;
}

/*****************************************************************************/
