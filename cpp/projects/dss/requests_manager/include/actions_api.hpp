/*****************************************************************************
Title: actions api - Infinity Labs R&D 
Group: RD91
Description: actions api API
******************************************************************************/

#ifndef ILRD_RD91_ACTIONS_API_HPP
#define ILRD_RD91_ACTIONS_API_HPP

#include <boost/shared_ptr.hpp> // boost::shared_ptr

namespace ilrd
{

class CallbackHandler
{
public:
    virtual ~CallbackHandler() = 0;
    virtual void operator()(bool status) = 0;
};    

class Action
{
public:
    Action(boost::shared_ptr<CallbackHandler> callback_);
    virtual ~Action() = 0;
    virtual void operator()() = 0;
    void Callback(bool status);

private:
    boost::shared_ptr<CallbackHandler> m_callback;
};

}

#endif // ILRD_RD91_ACTIONS_API_HPP
