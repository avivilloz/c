/*******************************************************************************
Title: Shapes
Group: Ol91
Description: Shapes drawing API
*******************************************************************************/

#ifndef ILRD_OL91_CIRCLE_HPP
#define ILRD_OL91_CIRCLE_HPP

#include "shape.hpp"

namespace ilrd
{
    class Circle : public Shape
    {
    public:
        void Draw() const;
    };
} 

#endif // ILRD_OL91_CIRCLE_HPP
