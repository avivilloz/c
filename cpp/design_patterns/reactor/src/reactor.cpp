/*****************************************************************************
Title: reactor - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: 
Description: reactor API
******************************************************************************/

#include "reactor.hpp" // api 

/*****************************************************************************/

namespace ilrd
{

Reactor::Reactor()
    : m_handlers(), m_demultiplexer(), m_shouldRun(1)
{}

Reactor::~Reactor()
{}

void Reactor::Run()
{
    m_shouldRun = 1;
    std::queue<Key_t> events;
    while (m_shouldRun)
    {
        m_demultiplexer.Select(events);
        while(!events.empty())
        {
            std::map<Key_t, Handler_t>::iterator it = m_handlers.find(events.front());
            if (it != m_handlers.end())
            {
                it->second();
            }
            events.pop();
        }
    } 
}

void Reactor::Stop()
{
    m_shouldRun = 0;
}

void Reactor::Register(int fd, Handler_t handler, EventType operation)
{
    m_handlers[std::make_pair(fd, operation)] = handler;
    m_demultiplexer.AddFd(fd, operation);
}

void Reactor::Unregister(int fd, EventType operation)
{
    m_handlers.erase(m_handlers.find(std::make_pair(fd, operation)));
    m_demultiplexer.RemoveFd(fd, operation);
}

}

/*****************************************************************************/
