/*****************************************************************************
Title: thread_pool - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: 
Description: thread_pool API
******************************************************************************/

#include "thread_pool.hpp" // api 

namespace ilrd
{

ThreadPool::ThreadPool(std::size_t nThreadsToLaunch)
    : m_workers(), m_tasks(), m_addTask(m_tasks), m_getTask(m_tasks),
    m_addThread(m_workers), m_stopThread(m_workers), m_removeThread(m_workers),
    m_threadLauncher(m_addThread, m_getTask), 
    m_threadRemover(m_addTask, m_stopThread, m_removeThread)
{
    m_threadLauncher.Launch(nThreadsToLaunch);
}

ThreadPool::~ThreadPool()
{
    Stop();
}

void ThreadPool::Add(Task_t task)
{
    m_addTask(task);
}

void ThreadPool::Stop()
{
    m_threadRemover.Remove(m_workers.size());
}

void ThreadPool::SetThreadsNum(std::size_t nThreadsToSet)
{
    std::size_t nThreads = m_workers.size();
    if (nThreadsToSet > nThreads)
    {
        m_threadLauncher.Launch(nThreadsToSet - nThreads);
    }
    else if (nThreadsToSet < nThreads)
    {
        m_threadRemover.Remove(nThreads - nThreadsToSet);
    }
}

}

/*****************************************************************************/
