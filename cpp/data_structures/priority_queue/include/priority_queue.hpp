/****************************************************************************
Title: THREAD POOL PQ - Infinity Labs R&D 
Group: RD91
Description: Thread Pool API
*****************************************************************************/

#ifndef ILRD_RD91_PQ_HPP
#define ILRD_RD91_PQ_HPP

#include <queue>

namespace ilrd
{

template<typename Type, typename CmpFunc>
class PriorityQueue
{
public:
    typedef Type value_type;

    PriorityQueue(): m_queue() {}
    ~PriorityQueue() {}

    void push(Type data)
    {
        m_queue.push(data);
    }
    void pop()
    {
        m_queue.pop();
    }
    Type front() 
    {
        return m_queue.top();
    }
    bool empty() const
    {
        return m_queue.empty();
    }
    std::size_t size() const
    {
        return m_queue.size();
    }
private:
    std::priority_queue<Type, std::vector<Type>, CmpFunc> m_queue;
};

}

#endif /* ILRD_RD91_PQ_HPP */
