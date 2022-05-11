/*****************************************************************************
Title: task_args - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: task_args
******************************************************************************/

#include <sys/types.h> // u_int32_t
#include <boost/shared_ptr.hpp> // boost::shared_ptr
#include <boost/thread/mutex.hpp> // boost::mutex

#include "nbd_task.hpp" // api
#include "framework.hpp" // Framework
#include "handleton.hpp" // Handleton
#include "requests_api.hpp" // RequestHandler
#include "commands_api.hpp" // Command

namespace ilrd
{

NBDTask::NBDTask(
    u_int32_t type_, 
    boost::shared_ptr<RequestHandler> request_, 
    boost::mutex &mutex_
)
    : m_type(type_), m_request(request_), m_mutex(mutex_)
{}

void NBDTask::operator()()
{
    boost::mutex::scoped_lock lock(m_mutex);
    Handleton<Framework> framework;
    boost::shared_ptr<Command> command(framework->Create(m_type, m_request));
    (*command)();
}

}

/*****************************************************************************/
