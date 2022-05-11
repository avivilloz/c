/*****************************************************************************
Title: thread_remover - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: thread_remover
******************************************************************************/

#include <vector>
#include <climits>

#include "thread_pool.hpp" // api

namespace ilrd
{

ThreadPool::ThreadRemover::ThreadRemover(
    AddTask &addTask, 
    StopThread &stopThread,
    RemoveThread &removeThread
) : m_addTask(addTask), m_stopThread(stopThread), 
    m_removeThread(removeThread), m_workersToRemove(), m_sem(0)
{}

void ThreadPool::ThreadRemover::Remove(std::size_t nThreadsToRemove)
{
    SendBadTasks(nThreadsToRemove);
    RemoveThreads(nThreadsToRemove);
}

void ThreadPool::ThreadRemover::SendBadTasks(std::size_t nThreadsToRemove)
{
    BadTask badTask(m_workersToRemove, m_sem);
    Task_t task(new RegularTask<BadTask>(badTask, UINT_MAX));

    for (std::size_t i = 0; i < nThreadsToRemove; ++i)
    {
        m_addTask(task);
    }
}

void ThreadPool::ThreadRemover::RemoveThreads(std::size_t nThreadsToRemove)
{
    std::vector<ThreadId_t> workersId;

    for (std::size_t i = 0; i < nThreadsToRemove; ++i)
    {
        ThreadId_t workerId;
        m_workersToRemove.Pop(workerId);
        workersId.push_back(workerId);
        m_stopThread(workerId);
    }

    for (std::size_t i = 0; i < nThreadsToRemove; ++i)
    {
        m_sem.post();
    }

    for (std::size_t i = 0; i < nThreadsToRemove; ++i)
    {
        m_removeThread(workersId[i]);
    }
}

ThreadPool::ThreadRemover::BadTask::BadTask(
    ThreadsIdQ_t &workersToRemove,
    Semaphore_t &sem
) : m_workersToRemove(workersToRemove), m_sem(sem)
{}

void ThreadPool::ThreadRemover::BadTask::operator()()
{
    m_workersToRemove.Push(boost::this_thread::get_id());
    m_sem.wait();
}

}

/*****************************************************************************/


