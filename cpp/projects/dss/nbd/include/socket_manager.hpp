/*****************************************************************************
Title: socket_manager - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: socket_manager
******************************************************************************/

#ifndef ILRD_OL91_SOCKET_MANAGER_HPP
#define ILRD_OL91_SOCKET_MANAGER_HPP

namespace ilrd
{

class SocketManager
{
public:
    SocketManager(int sk_);
    ~SocketManager();
    void Write(const char *buf, size_t len);
    void Read(char *buf, size_t len);

private:
    int m_sk;
};

}

#endif /*ILRD_OL91_SOCKET_MANAGER_HPP*/

/*****************************************************************************/
