/*****************************************************************************
Title: nbd_task - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: nbd_task
******************************************************************************/

#ifndef ILRD_OL91_NBD_TASK_HPP
#define ILRD_OL91_NBD_TASK_HPP

#include <linux/nbd.h> // struct nbd_reply
#include <sys/types.h> // u_int32_t
#include <boost/thread/mutex.hpp> // boost::mutex

#include "requests_api.hpp" // RequestHandler
#include "nbd_reply.hpp" // NBDReply
#include "input_proxy.hpp" // InputProxy::Task

namespace ilrd
{

class NBDTask : public InputProxy::Task
{
public:
    NBDTask(
        u_int32_t type_, 
        boost::shared_ptr<RequestHandler> request_, 
        boost::mutex &mutex_
    );
    void operator()();

private:
    u_int32_t m_type;
    boost::shared_ptr<RequestHandler> m_request;
    boost::mutex &m_mutex;
};

}

#endif /*ILRD_OL91_NBD_TASK_HPP*/

/*****************************************************************************/
