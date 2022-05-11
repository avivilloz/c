/*****************************************************************************
Title: Framework - Infinity Labs R&D 
Group: RD91
Description: Framework API
******************************************************************************/

#ifndef ILRD_RD91_FRAMEWORK_HPP
#define ILRD_RD91_FRAMEWORK_HPP

#include <boost/shared_ptr.hpp> // boost::shared_ptr
#include <sys/types.h> // u_int32_t

#include "thread_pool.hpp" // ThreadPool
#include "handleton.hpp" // Handleton
#include "plug_and_play.hpp" // PlugAndPlay
#include "input_mediator.hpp" // InputMediator
#include "input_proxy.hpp" // InputProxy
#include "factory.hpp" // Factory
#include "reactor.hpp" // Reactor::EventType
#include "commands_api.hpp" // Command
#include "requests_api.hpp" // RequestHandler

namespace ilrd
{

class Framework
{
public:
    void Register(boost::shared_ptr<InputProxy> inputProxy, 
                  Reactor::EventType event, int fd); 

    typedef boost::shared_ptr<Command> (*Creator_t)(
        boost::shared_ptr<RequestHandler>
    );

    void Add(u_int32_t type, Creator_t creator);
    boost::shared_ptr<Command> Create(
        u_int32_t type, boost::shared_ptr<RequestHandler> request
    );

private:
    ThreadPool m_pool;
    PlugAndPlay m_monitor;
    InputMediator m_mediator;
    Factory<
        boost::shared_ptr<Command>, 
        u_int32_t, 
        boost::shared_ptr<RequestHandler> 
    > m_commandsF;

    friend class Handleton<Framework>;
    Framework();

    std::size_t GetThreadsNum();
};

}

#endif // ILRD_RD91_FRAMEWORK_HPP

