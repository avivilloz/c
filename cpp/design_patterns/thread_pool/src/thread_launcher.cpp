/*****************************************************************************
Title: thread_launcher - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: thread_launcher
******************************************************************************/

#include "thread_pool.hpp" // api

namespace ilrd
{

ThreadPool::ThreadLauncher::ThreadLauncher(AddThread &addThread, GetTask &getTask) 
    : m_addThread(addThread), m_getTask(getTask)
{}

void ThreadPool::ThreadLauncher::Launch(std::size_t nThreadsToLaunch)
{
    for (std::size_t i = 0; i < nThreadsToLaunch; ++i)
    {
        m_addThread(Thread_t(new WorkerThread(m_getTask)));
    }
}

}

/*****************************************************************************/

