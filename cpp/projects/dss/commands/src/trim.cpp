/*****************************************************************************
Title: trim - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: trim
******************************************************************************/

#include <boost/shared_ptr.hpp> // boost::shared_ptr

#include "trim.hpp" // api
#include "requests_api.hpp" // RequestHandler

namespace ilrd
{

Trim::Trim(boost::shared_ptr<RequestHandler> request_)
    : Command(request_)
{}

void Trim::operator()()
{
    Command::m_request->Reply(0);
}

}

/*****************************************************************************/
