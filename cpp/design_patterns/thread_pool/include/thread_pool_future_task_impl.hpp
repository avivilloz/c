/*****************************************************************************
Title: future_task - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: future_task
******************************************************************************/

#include "thread_pool.hpp" // api

template <typename Func, typename T>
ThreadPool::FutureTask<Func, T>::FutureTask(Func action_, unsigned int priority_)
    : RegularTask<Func>(action_, priority_), m_result(), m_sem(0)
{}

template <typename Func, typename T>
ThreadPool::FutureTask<Func, T>::~FutureTask()
{}

template <typename Func, typename T>
void ThreadPool::FutureTask<Func, T>::Execute()
{
    m_result = ThreadPool::RegularTask<Func>::GetAction()();
    m_sem.post();
}

template <typename Func, typename T>
T ThreadPool::FutureTask<Func, T>::GetResult()
{
    m_sem.wait();
    return m_result;
}

/*****************************************************************************/
