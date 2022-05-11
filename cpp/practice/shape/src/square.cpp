/*****************************************************************************
Title: shapes - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: 
Description: shapes API
******************************************************************************/

#include "square.hpp" // api

using namespace ilrd;

/*****************************************************************************/

void Square::Draw() const
{
    for (std::size_t i = 0; i < GetOffset(); ++i)
    {
        std::cout << "\t";
    }
    std::cout << "square" << std::endl;
}

/*****************************************************************************/

