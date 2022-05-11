/*****************************************************************************
Title: worker_thread - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: worker_thread
******************************************************************************/

#include <boost/bind.hpp>

#include "thread_pool.hpp" // api

namespace ilrd
{

ThreadPool::WorkerThread::WorkerThread(GetTask &getTask)
    : m_shouldWork(true), m_thread(new boost::thread(
    boost::bind(&ThreadPool::WorkerThread::Work, this, getTask)))
{}

ThreadPool::WorkerThread::~WorkerThread()
{
    m_thread->join();
}

boost::thread::id ThreadPool::WorkerThread::GetId()
{
    return m_thread->get_id();
}

void ThreadPool::WorkerThread::Stop()
{
    m_shouldWork = false;
}

void ThreadPool::WorkerThread::Work(GetTask &getTask)
{
    while (m_shouldWork)
    {
        boost::shared_ptr<Task> task = getTask();
        task->Execute();
    }
}

}

/*****************************************************************************/

