/*****************************************************************************
Title: input_mediator - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: input_mediator
******************************************************************************/

#include <boost/thread.hpp>

#include "input_mediator.hpp" // api

/*****************************************************************************/

namespace ilrd
{

#define TASK_PRIORITY 0

InputMediator::InputMediator(ThreadPool& pool_)
    : m_pool(pool_), m_reactor(), m_proxies(),
    m_reactorThread(InputMediator::RunReactor(m_reactor))
{}

InputMediator::~InputMediator()
{
    m_reactor.Stop();
}

void InputMediator::Register(
    boost::shared_ptr<InputProxy> inputProxy_, 
    Reactor::EventType event_, int fd_
)
{
    m_proxies[std::make_pair(event_, fd_)] = inputProxy_;
    m_reactor.Register(fd_, Callback(*this, event_, fd_), event_);
}

void InputMediator::Notify(Reactor::EventType event, int fd)
{
    ExecuteTask taskWrapper(m_proxies[std::make_pair(event, fd)]->GetTask());

    boost::shared_ptr<ThreadPool::Task> task(
    new ThreadPool::RegularTask<ExecuteTask>(taskWrapper, TASK_PRIORITY));

    m_pool.Add(task);
}

InputMediator::Callback::Callback(
    InputMediator& inputMediator_, 
    Reactor::EventType event_, int fd_
)
    : m_inputMediator(inputMediator_), m_event(event_), m_fd(fd_)
{}

void InputMediator::Callback::operator()()
{
    m_inputMediator.Notify(m_event, m_fd);
}

InputMediator::RunReactor::RunReactor(Reactor &reactor_)
    : m_reactor(reactor_)
{}

void InputMediator::RunReactor::operator()()
{
    m_reactor.Run();
}

InputMediator::ExecuteTask::ExecuteTask(boost::shared_ptr<InputProxy::Task> task)
    : m_task(task)
{}

void InputMediator::ExecuteTask::operator()()
{
    (*m_task)();
}

}


/*****************************************************************************/

