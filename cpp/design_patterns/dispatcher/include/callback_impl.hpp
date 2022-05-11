/*****************************************************************************
Title: callback_impl - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: callback_impl
******************************************************************************/

#include <exception>

#include "dispatcher.hpp"

template<typename Message>
CallbackBase<Message>::CallbackBase()
    : m_dispatcher()
{}

template<typename Message>
CallbackBase<Message>::CallbackBase(const CallbackBase<Message>& other)
    : m_dispatcher()
{}

template<typename Message>
CallbackBase<Message>& CallbackBase<Message>::operator=(
    const CallbackBase<Message>& other
)
{
    return *this;
}

template<typename Message>
CallbackBase<Message>::~CallbackBase()
{}

template<typename Message>
Dispatcher<Message> *CallbackBase<Message>::GetDispatcher()
{
    return m_dispatcher;
}

template<typename Message>
void CallbackBase<Message>::SetDispatcher(Dispatcher<Message> *dispatcher)
{
    m_dispatcher = dispatcher;
}

template<typename Message, typename Receiver>
Callback<Message, Receiver>::Callback(
    Receiver &receiver, 
    void (Receiver::*msgHandler)(Message msg), 
    void (Receiver::*deathHandler)()
) : CallbackBase<Message>(), m_receiver(receiver), m_msgHandler(msgHandler), 
    m_deathHandler(deathHandler)
{
    if (NULL == msgHandler)
    {
        throw std::invalid_argument("incorrect usage: null msg handler");
    }
}

template<typename Message, typename Receiver>
Callback<Message, Receiver>::~Callback()
{
    if (NULL != CallbackBase<Message>::GetDispatcher())
    {
        CallbackBase<Message>::GetDispatcher()->Unregister(this);
    }
}

template<typename Message, typename Receiver>
void Callback<Message, Receiver>::Notify(Message msg)
{
    (m_receiver.*m_msgHandler)(msg);
}

template<typename Message, typename Receiver>
void Callback<Message, Receiver>::NotifyOnDeath()
{
    if (NULL != m_deathHandler)
    {
        (m_receiver.*m_deathHandler)();
    }
}
