/*****************************************************************************
Title: framework - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: 
Description: framework API
******************************************************************************/

#include <sys/types.h> // u_int32_t
#include <boost/shared_ptr.hpp> // boost::shared_ptr
#include <stdlib.h> // atoi

#include "framework.hpp" // api 
#include "handleton.hpp" // Handleton
#include "runtime_config.hpp" // RuntimeConfig
#include "commands_api.hpp" // Command
#include "requests_api.hpp" // RequestHandler
#include "input_proxy.hpp" // InputProxy
#include "reactor.hpp" // Reactor::EventType

/*****************************************************************************/

namespace ilrd
{

Framework::Framework()
    : m_pool(GetThreadsNum()), m_monitor(), m_mediator(m_pool), m_commandsF()
{}

void Framework::Register(
    boost::shared_ptr<InputProxy> inputProxy, 
    Reactor::EventType event, int fd
)
{
    m_mediator.Register(inputProxy, event, fd);
}

void Framework::Add(u_int32_t type, Creator_t creator)
{
    m_commandsF.Add(type, creator);
}

boost::shared_ptr<Command> Framework::Create(
    u_int32_t type, boost::shared_ptr<RequestHandler> request
)
{
    return m_commandsF.Create(type, request);
}

std::size_t Framework::GetThreadsNum()
{
    Handleton<RuntimeConfig> config;
    return atoi(config->GetValue(NUM_OF_THREADS).c_str());
}

}


/*****************************************************************************/
