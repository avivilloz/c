/*****************************************************************************
Title: quiz_generic_stack 
Description: learn quiz_generic_stack
******************************************************************************/

#include <iostream> // cout

using namespace std;

/*****************************************************************************/

template<class T, size_t N>
class Stack
{
public:
    Stack() : m_top(0) {}
    void Push(T value)
    {
        if (m_top == N)
        {
            throw out_of_range("error: stack is full");
        }

        m_container[m_top++] = value;
    }
    void Pop()
    {
        if (m_top == 0)
        {
            throw out_of_range("error: stack is empty");
        }

        --m_top;
    }
    T Peek()
    {
        if (m_top == 0)
        {
            throw out_of_range("error: stack is empty");
        }

        return m_container[m_top];
    }
    size_t Size()
    {
        return m_top;
    }
    bool IsEmpty()
    {
        return (0 == m_top);
    }
    void Print()
    {
        for (size_t i = 0; i < m_top; ++i)
        {
            cout << m_container[i] << " ";
        }
        cout << endl;
    }
private:
    T m_container[N];
    size_t m_top;
};

int main()
{
    Stack<int, 24> s;

    s.Push(35);
    s.Push(36);
    s.Push(37);
    s.Push(38);
    s.Push(39);
    s.Push(40);
    s.Push(35);
    s.Push(35);
    s.Push(35);
    s.Push(36);
    s.Push(37);
    s.Push(38);
    s.Push(39);
    s.Push(40);
    s.Push(36);
    s.Push(37);
    s.Push(38);
    s.Push(39);
    s.Push(40);
    s.Push(36);
    s.Push(37);
    s.Push(38);
    s.Push(39);
    s.Push(40);
    try
    {
        s.Push(40);
    }
    catch (const out_of_range& error)
    {
        cerr << error.what() << endl;
    }

    s.Print();

    s.Pop();
    s.Pop();
    s.Pop();
    s.Pop();
    s.Pop();
    s.Pop();
    s.Pop();
    s.Pop();
    s.Pop();
    s.Pop();
    s.Pop();
    s.Pop();
    s.Pop();
    s.Pop();
    s.Pop();
    s.Pop();
    s.Pop();
    s.Pop();
    s.Pop();
    s.Pop();
    s.Pop();
    s.Pop();
    s.Pop();
    s.Pop();
    try
    {
        s.Pop();
    }
    catch (const out_of_range& error)
    {
        cerr << error.what() << endl;
    }

    return 0;
}

/*****************************************************************************/

