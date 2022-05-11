/*****************************************************************************
Title: objects - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: objects
******************************************************************************/

#include "thread_pool.hpp" // api

class WorkerThread
{
public:
    WorkerThread(GetTask &getTask);
    ~WorkerThread();
    ThreadId_t GetId();
    void Stop();
private:
    void Work(GetTask &getTask);

    bool m_shouldWork;
    RawThread_t m_thread;
};

class ThreadLauncher
{
public:
    ThreadLauncher(AddThread &addThread, GetTask &getTask);
    void Launch(std::size_t nThreadsToLaunch);
private:
    AddThread &m_addThread;
    GetTask &m_getTask;
};

class ThreadRemover
{
public:
    typedef WaitableQueue<std::queue<boost::thread::id> > ThreadsIdQ_t;

    ThreadRemover(
        AddTask &addTask, 
        StopThread &stopThread, 
        RemoveThread &removeThread
    );
    void Remove(std::size_t nThreadsToRemove);
private:
    void SendBadTasks(std::size_t nThreadsToRemove);
    void RemoveThreads(std::size_t nThreadsToRemove);

    class BadTask
    {
    public:
        BadTask(ThreadsIdQ_t &workersToRemove, Semaphore_t &sem);
        void operator()();
    private:
        ThreadsIdQ_t &m_workersToRemove;
        Semaphore_t &m_sem;
    };

    AddTask &m_addTask;
    StopThread &m_stopThread;
    RemoveThread &m_removeThread;

    ThreadsIdQ_t m_workersToRemove;
    Semaphore_t m_sem;
};

/*****************************************************************************/
