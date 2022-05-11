/*****************************************************************************
Title: regular_task - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: regular_task
******************************************************************************/

#include "thread_pool.hpp" // api

template <typename Func>
ThreadPool::RegularTask<Func>::RegularTask(
    Func action_, unsigned int priority_
) : m_action(action_), m_priority(priority_)
{}

template <typename Func>
ThreadPool::RegularTask<Func>::~RegularTask()
{}

template <typename Func>
void ThreadPool::RegularTask<Func>::Execute()
{
    m_action();
}

template <typename Func>
unsigned int ThreadPool::RegularTask<Func>::GetPriority() const
{
    return m_priority;
}

template <typename Func>
Func ThreadPool::RegularTask<Func>::GetAction()
{
    return m_action;
}

/*****************************************************************************/
