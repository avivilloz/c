/*******************************************************************************
Title: Shapes
Group: Ol91
Description: Shapes drawing API
*******************************************************************************/

#ifndef ILRD_OL91_SHAPES_HPP
#define ILRD_OL91_SHAPES_HPP

#include <cstddef> // size_t
#include <iostream> // ostream
#include <list> // list

namespace ilrd
{
    class Shape
    {
    public:
        explicit Shape(size_t offset = 0);
        virtual ~Shape();
        Shape& Move(size_t offset_);
        void virtual Draw() const = 0;
        size_t GetOffset() const;
    private:
        size_t m_offset;
    };

    void PrintShapes(std::list<Shape*> shapes);
}

#endif //ILRD_OL91_SHAPES_HPP
