/*****************************************************************************
Title: shapes - Infinity Labs R&D 
Group: OL91
Author: Aviv
Description: shapes test
******************************************************************************/

#include <iostream> // cout

#include "shape.hpp" // api
#include "circle.hpp" // api
#include "square.hpp" // api
#include "line.hpp" // api
#include "rectangle.hpp" // api

using namespace std;
using namespace ilrd;

/*****************************************************************************/

int main()
{
    list<Shape*> shapes;

    shapes.push_back(new Circle);
    shapes.push_back(new Rectangle);
    shapes.push_back(new Square);
    shapes.push_back(new Line);

    shapes.front()->Move(5);
    shapes.back()->Move(10);

    PrintShapes(shapes);

    while (!shapes.empty())
    {
        delete shapes.front();
        shapes.pop_front();
    }

    return 0;
}

/*****************************************************************************/

