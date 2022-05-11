/*****************************************************************************
Title: shapes - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: 
Description: shapes API
******************************************************************************/

#include <iterator>

#include "shape.hpp" // api 

/*****************************************************************************/

namespace ilrd
{

Shape::Shape(std::size_t offset)
    : m_offset(offset)
{}

Shape::~Shape()
{}

Shape& Shape::Move(std::size_t offset_)
{
    m_offset = offset_;
    return *this;
}

std::size_t Shape::GetOffset() const
{
    return m_offset;
}

void PrintShapes(std::list<Shape*> shapes)
{
    std::list<Shape*>::iterator iter = shapes.begin();

    for (; iter != shapes.end(); ++iter)
    {
        (*iter)->Draw();
    }
}

}

/*****************************************************************************/

