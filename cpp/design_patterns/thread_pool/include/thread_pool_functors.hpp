/*****************************************************************************
Title: functors - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: functors
******************************************************************************/

#include "thread_pool.hpp" // api

class CmpFunc
{
public:
    bool operator()(const Task_t lhs, const Task_t rhs);
};

class AddTask
{
public:
    AddTask(TasksQ_t &tasks);
    void operator()(Task_t task);
private:
    TasksQ_t &m_tasks;
};

class GetTask
{
public:
    GetTask(TasksQ_t &tasks);
    Task_t operator()();
private:
    TasksQ_t &m_tasks;
};

class AddThread
{
public:
    AddThread(ThreadsMap_t &workers);
    void operator()(Thread_t worker);
private:
    ThreadsMap_t &m_workers;
};

class StopThread
{
public:
    StopThread(ThreadsMap_t &workers);
    void operator()(ThreadId_t workerId);
private:
    ThreadsMap_t &m_workers;
};

class RemoveThread
{
public:
    RemoveThread(ThreadsMap_t &workers);
    void operator()(ThreadId_t workerId);
private:
    ThreadsMap_t &m_workers;
};

/*****************************************************************************/
