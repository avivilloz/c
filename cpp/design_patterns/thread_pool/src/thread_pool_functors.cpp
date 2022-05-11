/*****************************************************************************
Title: cmp_func - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: cmp_func
******************************************************************************/

#include "thread_pool.hpp" // api

namespace ilrd
{

ThreadPool::AddTask::AddTask(TasksQ_t &tasks)
    : m_tasks(tasks)
{}

void ThreadPool::AddTask::operator()(Task_t task)
{
    m_tasks.Push(task);
}

ThreadPool::GetTask::GetTask(TasksQ_t &tasks)
    : m_tasks(tasks)
{}

ThreadPool::Task_t ThreadPool::GetTask::operator()()
{
    Task_t task;
    m_tasks.Pop(task);
    return task;
}

ThreadPool::AddThread::AddThread(ThreadsMap_t &workers)
    : m_workers(workers)
{}

void ThreadPool::AddThread::operator()(Thread_t worker)
{
    m_workers[worker->GetId()] = worker;
}

ThreadPool::StopThread::StopThread(ThreadsMap_t &workers)
    : m_workers(workers)
{}

void ThreadPool::StopThread::operator()(ThreadId_t workerId)
{
    m_workers[workerId]->Stop();
}

ThreadPool::RemoveThread::RemoveThread(ThreadsMap_t &workers)
    : m_workers(workers)
{}

void ThreadPool::RemoveThread::operator()(ThreadId_t workerId)
{
    m_workers.erase(workerId);
}

bool ThreadPool::CmpFunc::operator()(const Task_t lhs, const Task_t rhs) 
{ 
    return lhs->GetPriority() >= rhs->GetPriority(); 
}

}

/*****************************************************************************/

