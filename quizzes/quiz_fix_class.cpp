/*****************************************************************************
Title: quiz_fix_class 
Description: learn quiz_fix_class
******************************************************************************/

#include <iostream> // cout
#include <cstring> // memcpy

using namespace std;

/*****************************************************************************/

class Stack
{
public:
    Stack(int capacity)
        : m_container(new int[capacity]), m_capacity(capacity), m_top(-1)
    {}
    Stack(const Stack& other)
        : m_container(new int[other.m_capacity]), m_capacity(other.m_capacity),
        m_top(other.m_top)
    {
        memcpy(m_container, other.m_container, other.m_top + 1);
    }
    ~Stack()
    {
        delete[] m_container;
    }
    Stack& operator=(const Stack& other)
    {
        if (this == &other)
        {
            return *this;
        }

        delete[] m_container;
        m_container = new int[other.m_capacity];
        memcpy(m_container, other.m_container, other.m_top + 1);
        m_capacity = other.m_capacity;
        m_top = other.m_top;

        return *this;
    }

    int Push(int num)
    {
        if (m_top == m_capacity)
        {
            cerr << "error: container is full" << endl;
            return 1;
        }

        ++m_top;
        m_container[m_top] = num;

        return 0;
    }
    int Pop(void)
    {
        if (m_top < 0)
        {
            cerr << "error: container is empty" << endl;
            return 1;
        }

        int temp = m_container[m_top];
        --m_top;

        return temp;
    }
    void Print(void)
    {
        for (int i = 0; i <= m_top; ++i)
        {
            cout << m_container[i];
        }
        cout << endl;
    }

private:
    int *m_container;
    int m_capacity;
    int m_top;
};

int main()
{
    Stack s1(3);
    s1.Push(2);
    s1.Push(3);
    s1.Push(1);
    Stack s2 = s1;

    s1.Print();
    s2.Print();

    s1.Push(5);
    s2.Push(5);

    for (int i = 0; i < 4; ++i)
    {
        s1.Pop();
        s2.Pop();
    }

    return 0;
}

/*****************************************************************************/

