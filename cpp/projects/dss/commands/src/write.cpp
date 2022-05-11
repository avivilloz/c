/*****************************************************************************
Title: write - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: write
******************************************************************************/

#include <boost/shared_ptr.hpp> // boost::shared_ptr

#include "write.hpp" // api
#include "requests_api.hpp" // RequestHandler

namespace ilrd
{

Write::Write(boost::shared_ptr<RequestHandler> request_)
    : Command(request_)
{}

extern void (*g_write)(boost::shared_ptr<RequestHandler> request);

void Write::operator()()
{
    g_write(Command::m_request);
}

}

/*****************************************************************************/
