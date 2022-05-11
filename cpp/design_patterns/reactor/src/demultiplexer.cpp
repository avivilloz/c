/*****************************************************************************
Title: demultiplexer - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: demultiplexer
******************************************************************************/

#include <sys/time.h> // timeval
#include <unistd.h> // select
#include <string.h> // strerror
#include <errno.h> // errno

#include "reactor.hpp" // api
#include "helper.hpp"

/*****************************************************************************/

namespace ilrd
{

#define TIMEOUT 0

Reactor::Demultiplexer::Demultiplexer()
    : m_sets()
{
    for (std::size_t i = 0; i < NUM_OF_SETS; ++i)
    {
        FD_ZERO(&m_sets[i]);
    }
}

void Reactor::Demultiplexer::Select(std::queue<Key_t> &events)
{
    fd_set sets[NUM_OF_SETS];

    for (std::size_t i = 0; i < NUM_OF_SETS; ++i)
    {
        sets[i] = m_sets[i];
    }

    struct timeval timeout = {TIMEOUT, 0};

    int readyFds = select(FD_SETSIZE, 
                        &sets[READ], 
                        &sets[WRITE], 
                        &sets[EXCEPTION], 
                        &timeout);

    ThrowIfBad<std::runtime_error>(-1 == readyFds, strerror(errno));

    if (0 != readyFds)
    {
        for (std::size_t i = 0; i < FD_SETSIZE; ++i)
        {
            for (std::size_t j = 0; j < NUM_OF_SETS; ++j)
            {
                if(FD_ISSET(i, &sets[j]))
                {
                    events.push(std::make_pair(i, static_cast<EventType>(j)));
                }
            }
        }
    }
}

void Reactor::Demultiplexer::AddFd(int fd, EventType operation)
{
    FD_SET(fd, &m_sets[operation]);
}

void Reactor::Demultiplexer::RemoveFd(int fd, EventType operation)
{
    FD_CLR(fd, &m_sets[operation]);
}

}

/*****************************************************************************/

