/*****************************************************************************
Title: dispatcher_impl - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: dispatcher_impl
******************************************************************************/

#include <boost/shared_ptr.hpp>

#include "dispatcher.hpp"

template<typename Message>
Dispatcher<Message>::Dispatcher()
    : m_callbacks(), m_mutex()
{}

template<typename Message>
Dispatcher<Message>::~Dispatcher()
{
    typename std::list<CallbackBase<Message>*>::iterator it;
    boost::mutex::scoped_lock lock(m_mutex);
    for (it = m_callbacks.begin(); m_callbacks.end() != it; ++it)
    {
        (*it)->NotifyOnDeath(); 
        (*it)->m_dispatcher = NULL;
    } 
}

template<typename Message>
void Dispatcher<Message>::Dispatch(const Message& msg)
{
    typename std::list<CallbackBase<Message>*>::iterator it;
    boost::mutex::scoped_lock lock(m_mutex);
    for (it = m_callbacks.begin(); m_callbacks.end() != it; ++it)
    {
        (*it)->Notify(msg); 
    } 
}

template<typename Message>
void Dispatcher<Message>::Register(
    CallbackBase<Message> *callback
)
{
    callback->SetDispatcher(this);
    boost::mutex::scoped_lock lock(m_mutex);
    m_callbacks.push_back(callback);
}

template<typename Message>
void Dispatcher<Message>::Unregister(
    CallbackBase<Message> *callback
)
{
    typename std::list<CallbackBase<Message>*>::iterator it;
    boost::mutex::scoped_lock lock(m_mutex);
    for (it = m_callbacks.begin(); m_callbacks.end() != it; ++it)
    {   
        if (*it == callback)
        {
            m_callbacks.erase(it);
            break;
        }
    } 
}

/*****************************************************************************/
