/*****************************************************************************
Title: read - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: read
******************************************************************************/

#include <boost/shared_ptr.hpp> // boost::shared_ptr

#include "read.hpp" // api 
#include "requests_api.hpp" // RequestHandler

namespace ilrd
{

Read::Read(boost::shared_ptr<RequestHandler> request_)
    : Command(request_)
{}

extern void (*g_read)(boost::shared_ptr<RequestHandler> request);

void Read::operator()()
{
    g_read(Command::m_request);
}

}

/*****************************************************************************/
