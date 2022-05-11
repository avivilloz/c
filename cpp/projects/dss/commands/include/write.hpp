/*****************************************************************************
Title: write - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: write
******************************************************************************/

#ifndef ILRD_OL91_WRITE_HPP
#define ILRD_OL91_WRITE_HPP

#include <boost/shared_ptr.hpp> // boost::shared_ptr

#include "commands_api.hpp" // Command
#include "requests_api.hpp" // RequestHandler

namespace ilrd
{

class Write : public Command
{
public:
    Write(boost::shared_ptr<RequestHandler> request_);
    void operator()();
};

}

#endif /*ILRD_OL91_WRITE_HPP*/

/*****************************************************************************/
