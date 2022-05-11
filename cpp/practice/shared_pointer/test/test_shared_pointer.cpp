/*****************************************************************************
Title: shared_pointer - Infinity Labs R&D 
Group: OL91
Author: Aviv
Description: shared_pointer test
******************************************************************************/

#include <iostream> // cout

#include "shared_pointer.hpp" // api

using namespace std;
using namespace ilrd;

/*****************************************************************************/

class x
{
public:
    x() : i(1), c('a'), f(1.1) {}
    virtual ~x() {};
    virtual int GetI() {return i;}
    virtual char GetC() {return c;}
    virtual float GetF() {return f;}
private:
    int i;
    char c;
    float f;
};

class y : public x
{
public:
    y() : x(), i2(2), c2('b'), f2(2.2) {}
    int GetI() {return i2;}
    char GetC() {return c2;}
    float GetF() {return f2;}
private:
    int i2;
    char c2;
    float f2;
};

int main()
{
    cout << "testing operator constructor and * operator:" << endl;
    SharedPointer<int> sp1(new int(7));
    SharedPointer<char> sp2(new char('a'));
    SharedPointer<x> sp3(new x());
    cout << *sp1 << endl;
    cout << *sp2 << endl;
    cout << sp3->GetI() << sp3->GetC() << sp3->GetF() << endl;

    cout << "testing counting:" << endl;
    cout << sp3.Count() << endl;
    SharedPointer<x> sp4(sp3);
    cout << sp3.Count() << endl;
    SharedPointer<x> sp5(sp4);
    cout << sp3.Count() << endl;
    {
    SharedPointer<x> sp6(sp5);
    cout << sp3.Count() << endl;
    }
    SharedPointer<x> sp7(sp5);
    cout << sp3.Count() << endl;
    
    cout << "testing regular assign operator:" << endl;
    SharedPointer<int> sp8(new int(9));
    cout << *sp8 << endl;
    sp8 = sp1;
    cout << *sp8 << endl;

    SharedPointer<y> sp9(new y());
    cout << "testing casting copy constructor:" << endl;
    SharedPointer<x> sp10(new y());
    cout << (*sp10).GetI() << (*sp10).GetC() << (*sp10).GetF() << endl;
    cout << "testing casting assign:" << endl;
    sp3 = sp9;
    cout << (*sp3).GetI() << (*sp3).GetC() << (*sp3).GetF() << endl;
    


    return 0;
}

/*****************************************************************************/

