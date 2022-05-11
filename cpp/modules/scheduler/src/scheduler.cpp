/*****************************************************************************
Title: scheduler - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: 
Description: scheduler API
******************************************************************************/

#include <boost/shared_ptr.hpp> // boost::shared_ptr
#include <boost/asio.hpp> // boost::asio::deadline_timer
#include <boost/date_time/posix_time/posix_time.hpp> // boost::posix_time
#include <boost/thread/mutex.hpp> // boost::mutex::scoped_lock
#include <boost/bind.hpp> // boost::bind

#include "scheduler.hpp" // api 

namespace ilrd
{

Scheduler::Task::~Task()
{}

Scheduler::Scheduler()
    : m_io(), m_shouldRun(true), m_runThread(boost::bind(&Scheduler::Run, this))
{}

Scheduler::~Scheduler()
{
    m_shouldRun = false;
    m_io.stop();
    m_runThread.join();
}

void Scheduler::AddTask(
    boost::shared_ptr<Scheduler::Task> task,
    std::size_t delay
)
{
    boost::shared_ptr<boost::asio::deadline_timer> timer(
        new boost::asio::deadline_timer(m_io));

    timer->expires_from_now(boost::posix_time::seconds(delay));

    timer->async_wait(boost::bind(&Scheduler::ExecuteTask, this, 
        boost::asio::placeholders::error, timer, task));
}

void Scheduler::Run()
{
    while (m_shouldRun)
    {
        m_io.restart();
        m_io.run();
    }   
}

void Scheduler::ExecuteTask(
    const boost::system::error_code &err,
    boost::shared_ptr<boost::asio::deadline_timer> timer,
    boost::shared_ptr<Scheduler::Task> task
)
{ 
    (void)timer;
    if (!err)
    {
        task->Execute();
    }
}

}
