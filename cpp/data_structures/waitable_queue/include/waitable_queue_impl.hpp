/*****************************************************************************
Title: waitable_queue - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: 
Description: waitable_queue API
******************************************************************************/

#include "waitable_queue.hpp" // api 

template<typename Queue>
WaitableQueue<Queue>::WaitableQueue() 
   : m_queue(), m_mutex(), m_sem(0) 
{}

template<typename Queue>
WaitableQueue<Queue>::~WaitableQueue()
{}

template<typename Queue>
void WaitableQueue<Queue>::Push(const datatype& data)
{
   boost::mutex::scoped_lock lock(m_mutex);
   m_queue.push(data);
   m_sem.post();
}

template<typename Queue>
void WaitableQueue<Queue>::Pop(datatype &value_)
{
   m_sem.wait();
   boost::mutex::scoped_lock lock(m_mutex);
   value_ = m_queue.front();
   m_queue.pop();
}

template<typename Queue>
bool WaitableQueue<Queue>::Pop(
    datatype &value_, 
    boost::posix_time::time_duration& timer_
)
{
   boost::posix_time::ptime time(
     boost::posix_time::microsec_clock::universal_time());

   if (false == m_sem.timed_wait(time + timer_))
   {
      return 1;
   }

   boost::mutex::scoped_lock lock(m_mutex);
   value_ = m_queue.front();
   m_queue.pop();

   return 0;
}

template<typename Queue>
bool WaitableQueue<Queue>::IsEmpty() const
{
   boost::mutex::scoped_lock lock(m_mutex);
   return m_queue.empty(); 
}

template<typename Queue>
std::size_t WaitableQueue<Queue>::Size() const
{
   boost::mutex::scoped_lock lock(m_mutex);
   return m_queue.size(); 
}

/*****************************************************************************/
