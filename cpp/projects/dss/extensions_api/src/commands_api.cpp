/*****************************************************************************
Title: commands api - Infinity Labs R&D 
Group: OL91
Author: Aviv
Description: any command plugin needs to derive or use classes from this api.
******************************************************************************/

#include <boost/shared_ptr.hpp> // boost::shared_ptr

#include "commands_api.hpp" // api
#include "requests_api.hpp" // RequestHandler

namespace ilrd
{

Command::Command(boost::shared_ptr<RequestHandler> request_)
    : m_request(request_)
{}

Command::~Command()
{}

}

/****************************************************************************/
