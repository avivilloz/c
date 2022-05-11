/*****************************************************************************
Title: dispatcher - Infinity Labs R&D 
Group: OL91
Description: dispatcher API
******************************************************************************/

#ifndef ILRD_RD91_DISPATCHER_HPP
#define ILRD_RD91_DISPATCHER_HPP

#include <list>
#include <boost/core/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>

namespace ilrd
{

template<typename Message>
class Dispatcher;

template<typename Message>
class CallbackBase : private boost::noncopyable
{
public:
    CallbackBase();
    CallbackBase(const CallbackBase<Message>& other);
    CallbackBase<Message>& operator=(const CallbackBase<Message>& other);
    virtual ~CallbackBase() = 0;

protected:
    Dispatcher<Message> *GetDispatcher();    

private:
    Dispatcher<Message> *m_dispatcher;

    friend class Dispatcher<Message>;

    virtual void Notify(Message msg) = 0;
    virtual void NotifyOnDeath() = 0;
    void SetDispatcher(Dispatcher<Message> *dispatcher);
};

template<typename Message, typename Receiver>
class Callback : public CallbackBase<Message>
{
public:
    Callback(
        Receiver &receiver, 
        void (Receiver::*msgHandler)(Message msg), 
        void (Receiver::*deathHandler)() = 0
    );
    ~Callback();

private:
    Receiver &m_receiver;
    void (Receiver::*m_msgHandler)(Message msg); 
    void (Receiver::*m_deathHandler)();

    void Notify(Message msg);
    void NotifyOnDeath();
};

template<typename Message>
class Dispatcher : private boost::noncopyable
{
public:
    Dispatcher();
    ~Dispatcher();

    void Dispatch(const Message& msg);

    void Register(CallbackBase<Message> *callback);
    void Unregister(CallbackBase<Message> *callback);

private:
    friend class CallbackBase<Message>;
    std::list<CallbackBase<Message> *> m_callbacks;
    boost::mutex m_mutex;
};

#include "callback_impl.hpp"
#include "dispatcher_impl.hpp"

}

#endif // ILRD_RD91_DISPATCHER_HPP
