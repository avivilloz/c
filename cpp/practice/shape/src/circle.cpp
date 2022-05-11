/*****************************************************************************
Title: shapes - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: 
Description: shapes API
******************************************************************************/

#include "circle.hpp" // api

using namespace ilrd;

/*****************************************************************************/

void Circle::Draw() const
{
    for (std::size_t i = 0; i < GetOffset(); ++i)
    {
        std::cout << "\t";
    }
    std::cout << "circle" << std::endl;
}

/*****************************************************************************/

