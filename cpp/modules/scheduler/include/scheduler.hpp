/*****************************************************************************
Title: scheduler - Infinity Labs R&D 
Group: OL91
Description: scheduler API
******************************************************************************/

#ifndef ILRD_RD91_SCHEDULER_HPP
#define ILRD_RD91_SCHEDULER_HPP

#include <boost/core/noncopyable.hpp> // boost::noncopyable
#include <boost/shared_ptr.hpp> // boost::shared_ptr
#include <boost/thread.hpp> // boost::thread
#include <boost/thread/mutex.hpp> // boost::mutex
#include <boost/asio.hpp> // boost::asio::io_context

#include "handleton.hpp" // Handleton

namespace ilrd
{

class Scheduler : private boost::noncopyable
{
public:
    ~Scheduler();

    class Task
    {
    public:
        virtual ~Task() = 0;
        virtual void Execute() = 0;
    };

    void AddTask(boost::shared_ptr<Scheduler::Task> task, std::size_t delay);

private:
    boost::asio::io_context m_io;
    bool m_shouldRun;
    boost::thread m_runThread;

    friend class Handleton<Scheduler>;
    Scheduler();

    void Run();
    void ExecuteTask(
        const boost::system::error_code &err,
        boost::shared_ptr<boost::asio::deadline_timer> timer,
        boost::shared_ptr<Scheduler::Task> task
    );
};

}

#endif // ILRD_RD91_SCHEDULER_HPP
