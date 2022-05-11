/*****************************************************************************
Title: read - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: read
******************************************************************************/

#ifndef ILRD_OL91_READ_HPP
#define ILRD_OL91_READ_HPP

#include <boost/shared_ptr.hpp> // boost::shared_ptr

#include "commands_api.hpp" // Command
#include "requests_api.hpp" // RequestHandler

namespace ilrd
{

class Read : public Command
{
public:
    Read(boost::shared_ptr<RequestHandler> request_);
    void operator()();
};

}

#endif /*ILRD_OL91_READ_HPP*/

/*****************************************************************************/
