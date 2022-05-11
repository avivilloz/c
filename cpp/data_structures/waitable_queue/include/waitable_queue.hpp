/*****************************************************************************
Title: waitable_queue - Infinity Labs R&D 
Group: OL91
Description: waitable_queue API
******************************************************************************/

#ifndef ILRD_RD91_WAITABLE_QUEUE_HPP
#define ILRD_RD91_WAITABLE_QUEUE_HPP

#include <cstddef> // std::size_t
#include <boost/chrono.hpp> // boost::chrono
#include <boost/thread/mutex.hpp>   // boost::mutex
#include <boost/interprocess/sync/interprocess_semaphore.hpp> // boost::semaphore
#include <boost/date_time/posix_time/posix_time.hpp> // all posix time types

namespace ilrd
{

template<typename Queue>
class WaitableQueue
{
typedef typename Queue::value_type datatype;
public:
    WaitableQueue();
    ~WaitableQueue();
    void Push(const datatype &data);
    void Pop(datatype &value_);
    bool Pop(datatype &value_, boost::posix_time::time_duration& timer_);
    bool IsEmpty() const;
    std::size_t Size() const;
private:
    Queue m_queue;
    mutable boost::mutex m_mutex;
    boost::interprocess::interprocess_semaphore m_sem;
};

#include "waitable_queue_impl.hpp"

}

#endif // ILRD_RD91_WAITABLE_QUEUE_HPP

/*****************************************************************************/
