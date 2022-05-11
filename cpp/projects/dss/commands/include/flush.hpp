/*****************************************************************************
Title: flush - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: flush
******************************************************************************/

#ifndef ILRD_OL91_FLUSH_HPP
#define ILRD_OL91_FLUSH_HPP

#include <boost/shared_ptr.hpp> // boost::shared_ptr

#include "commands_api.hpp" // Command
#include "requests_api.hpp" // RequestHandler

namespace ilrd
{

class Flush : public Command
{
public:
    Flush(boost::shared_ptr<RequestHandler> request_);
    void operator()();
};

}

#endif /*ILRD_OL91_FLUSH_HPP*/

/*****************************************************************************/
