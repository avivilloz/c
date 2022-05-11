/*****************************************************************************
Title: tasks - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: tasks
******************************************************************************/

#include "thread_pool.hpp" // api

class Task
{
public:
    Task();
    virtual ~Task() = 0;
    virtual void Execute();
    virtual unsigned int GetPriority() const = 0;
};

template <typename Func>
class RegularTask : public Task
{
public:
    RegularTask(Func action_, unsigned int priority_);
    ~RegularTask();
    void Execute();
    unsigned int GetPriority() const;
protected:
    Func GetAction();
private:
    Func m_action;
    unsigned int m_priority;
};

template <typename Func, typename T>
class FutureTask : public RegularTask<Func>
{
public:
    FutureTask(Func action_, unsigned int priority_);
    ~FutureTask();
    void Execute();
    T GetResult();
private:
    T m_result;
    Semaphore_t m_sem;
};

/*****************************************************************************/
