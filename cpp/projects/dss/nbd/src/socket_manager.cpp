/*****************************************************************************
Title: socket_manager - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: socket_manager
******************************************************************************/

#include <unistd.h> // close, write, read
#include <errno.h> // errno
#include <string.h> // strerror
#include <stdexcept> // std::runtime_error

#include "socket_manager.hpp" // api
#include "helper.hpp" // ThrowIfBad

namespace ilrd
{

SocketManager::SocketManager(int sk_)
    : m_sk(sk_)
{}

SocketManager::~SocketManager()
{
    int status = close(m_sk);
    ThrowIfBad<std::runtime_error>(-1 == status, strerror(errno));
}

void SocketManager::Write(const char *buf, size_t len)
{
    while (len > 0) 
    {
        int nBytesWritten = write(m_sk, buf, len);
        ThrowIfBad<std::runtime_error>(-1 == nBytesWritten, strerror(errno));
        buf += nBytesWritten;
        len -= nBytesWritten;
    }
}

void SocketManager::Read(char *buf, size_t len)
{
    while (len > 0) 
    {
        int nBytesRead = read(m_sk, buf, len);
        ThrowIfBad<std::runtime_error>(-1 == nBytesRead, strerror(errno));
        buf += nBytesRead;
        len -= nBytesRead;
    }
}

}

/*****************************************************************************/

