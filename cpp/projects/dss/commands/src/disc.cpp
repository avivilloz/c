/*****************************************************************************
Title: disc - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: disc
******************************************************************************/

#include <boost/shared_ptr.hpp> // boost::shared_ptr

#include "disc.hpp" // api
#include "requests_api.hpp" // RequestHandler

namespace ilrd
{

Disc::Disc(boost::shared_ptr<RequestHandler> request_)
    : Command(request_)
{}

void Disc::operator()()
{
    Command::m_request->Reply(0);
    exit(0);
}

}

/*****************************************************************************/
