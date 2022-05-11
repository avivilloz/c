/*****************************************************************************
Title: commands api - Infinity Labs R&D 
Group: OL91
Author: Aviv
Description: any command plugin needs to derive or use classes from this api.
******************************************************************************/

#ifndef ILRD_RD91_COMMANDS_API_HPP
#define ILRD_RD91_COMMANDS_API_HPP

#include <boost/shared_ptr.hpp> // boost::shared_ptr

#include "requests_api.hpp" // RequestArgs, RequestHandler

namespace ilrd
{

class Command
{
public:
    Command(boost::shared_ptr<RequestHandler> request_);
    virtual ~Command() = 0;
    virtual void operator()() = 0;

protected:
    boost::shared_ptr<RequestHandler> m_request;
};

template<class T>
boost::shared_ptr<Command> CommandCreator(
    boost::shared_ptr<RequestHandler> request
)
{
    return boost::shared_ptr<Command>(new T(request));
}

}

#endif // ILRD_RD91_COMMANDS_API_HPP

/*****************************************************************************/

