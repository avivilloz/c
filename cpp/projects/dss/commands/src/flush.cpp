/*****************************************************************************
Title: flush - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: flush
******************************************************************************/

#include <boost/shared_ptr.hpp> // boost::shared_ptr

#include "flush.hpp" // api
#include "requests_api.hpp" // RequestHandler

namespace ilrd
{

Flush::Flush(boost::shared_ptr<RequestHandler> request_)
    : Command(request_)
{}

void Flush::operator()()
{
    Command::m_request->Reply(0);
}

}

/*****************************************************************************/
