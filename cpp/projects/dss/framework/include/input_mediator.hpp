/*****************************************************************************
Title: input_mediator - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: input_mediator
******************************************************************************/

#ifndef ILRD_OL91_INPUT_MEDIATOR_HPP
#define ILRD_OL91_INPUT_MEDIATOR_HPP

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp> 

#include "input_proxy.hpp"
#include "thread_pool.hpp"
#include "reactor.hpp"

namespace ilrd
{

class InputMediator
{
public:
    InputMediator(ThreadPool& pool_);
    ~InputMediator();

    void Register(
        boost::shared_ptr<InputProxy> inputProxy_, Reactor::EventType event_, int fd_
    );

private:
    class Callback
    {
    public:
        Callback(InputMediator& inputMediator_, Reactor::EventType event_, int fd_);
        void operator()();

    private:
        InputMediator& m_inputMediator;
        Reactor::EventType m_event;
        int m_fd;
    };

    class ExecuteTask
    {
    public:
        ExecuteTask(boost::shared_ptr<InputProxy::Task> task);
        void operator()();

    private:
        boost::shared_ptr<InputProxy::Task> m_task;
    };

    class RunReactor
    {
    public:
        RunReactor(Reactor &reactor_);
        void operator()();

    private:
        Reactor &m_reactor;
    };

    typedef std::pair<Reactor::EventType, int> ProxyKey_t;
    typedef std::map<ProxyKey_t, boost::shared_ptr<InputProxy> > ProxiesMap_t; 

    ThreadPool& m_pool;
    Reactor m_reactor;
    ProxiesMap_t m_proxies;
    boost::thread m_reactorThread;

    void Notify(Reactor::EventType event, int fd);
};

}

#endif /*ILRD_OL91_INPUT_MEDIATOR_HPP*/

/*****************************************************************************/
