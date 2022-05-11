/*****************************************************************************
Title: trim - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: trim
******************************************************************************/

#ifndef ILRD_OL91_TRIM_HPP
#define ILRD_OL91_TRIM_HPP

#include <boost/shared_ptr.hpp> // boost::shared_ptr

#include "commands_api.hpp" // Command
#include "requests_api.hpp" // RequestHandler

namespace ilrd
{

class Trim : public Command
{
public:
    Trim(boost::shared_ptr<RequestHandler> request_);
    void operator()();
};

}

#endif /*ILRD_OL91_TRIM_HPP*/

/*****************************************************************************/
