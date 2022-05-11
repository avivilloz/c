/*****************************************************************************
Title: thread_pool - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: thread_pool
******************************************************************************/

#ifndef ILRD_RD91_THREAD_POOL_HPP
#define ILRD_RD91_THREAD_POOL_HPP

#include <map>
#include <boost/thread/thread.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

#include "waitable_queue.hpp"
#include "priority_queue.hpp"

namespace ilrd
{

class ThreadPool : private boost::noncopyable
{
public:
    typedef boost::shared_ptr<boost::thread> RawThread_t;
    typedef boost::thread::id ThreadId_t;
    typedef boost::interprocess::interprocess_semaphore Semaphore_t;

    class Task;
    template <typename Func>
    class RegularTask;
    template <typename Func, typename T>
    class FutureTask;

    typedef boost::shared_ptr<Task> Task_t;

    #include "thread_pool_tasks.hpp"

    explicit ThreadPool(std::size_t nThreadsToLaunch);
    ~ThreadPool();

    void Add(Task_t task);
    void Stop();
    void SetThreadsNum(std::size_t nThreadsToSet);

private:
    class CmpFunc;
    class AddTask;
    class GetTask;
    class AddThread;
    class StopThread;
    class RemoveThread;
    class WorkerThread;

    class ThreadLauncher;
    class ThreadRemover;

    typedef boost::shared_ptr<WorkerThread> Thread_t;
    typedef std::map<ThreadId_t, Thread_t > ThreadsMap_t;
    typedef WaitableQueue<PriorityQueue<Task_t, CmpFunc> > TasksQ_t;

    #include "thread_pool_functors.hpp"
    #include "thread_pool_workers.hpp"

    ThreadsMap_t m_workers;
    TasksQ_t m_tasks;

    AddTask m_addTask;
    GetTask m_getTask;
    AddThread m_addThread;
    StopThread m_stopThread;
    RemoveThread m_removeThread;

    ThreadLauncher m_threadLauncher;
    ThreadRemover m_threadRemover;
};

#include "thread_pool_regular_task_impl.hpp"
#include "thread_pool_future_task_impl.hpp"

} // end of namespace ilrd

#endif /*ILRD_RD91_THREAD_POOL_HPP*/

/*****************************************************************************/
