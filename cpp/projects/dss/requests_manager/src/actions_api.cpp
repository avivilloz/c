/*****************************************************************************
Title: action api - Infinity Labs R&D 
Group: RD91
Description: action api API
******************************************************************************/

#include <boost/shared_ptr.hpp> // boost::shared_ptr

#include "actions_api.hpp" // api

namespace ilrd
{

CallbackHandler::~CallbackHandler()
{}

Action::Action(boost::shared_ptr<CallbackHandler> callback_)
    : m_callback(callback_)
{}

Action::~Action()
{}

void Action::Callback(bool status)
{
    (*m_callback)(status);
}

}
