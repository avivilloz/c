/*****************************************************************************
Title: input_proxy_nbd - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: input_proxy_nbd
******************************************************************************/

#ifndef ILRD_OL91_INPUT_PROXY_NBD_HPP
#define ILRD_OL91_INPUT_PROXY_NBD_HPP

#include <sys/types.h> // u_int32_t
#include <boost/shared_ptr.hpp> // boost::shared_ptr
#include <boost/thread/mutex.hpp> // boost::mutex

#include "socket_manager.hpp" // SocketManager
#include "input_proxy.hpp" // InputProxyBase

namespace ilrd
{

class NBDProxy : public InputProxy
{
public:
    NBDProxy(int sk_);
    boost::shared_ptr<InputProxy::Task> GetTask();

private:
    SocketManager m_skM;
    boost::mutex m_mutex;
};

}

#endif /*ILRD_OL91_INPUT_PROXY_NBD_HPP*/

/*****************************************************************************/
