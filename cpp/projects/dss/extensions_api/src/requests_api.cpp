/*****************************************************************************
Title: requests api - Infinity Labs R&D 
Group: OL91
Author: Aviv
Description: any command plugin needs to derive or use classes from this api.
******************************************************************************/

#include <sys/types.h> // u_int32_t, u_int64_t 
#include <boost/shared_ptr.hpp> // boost::shared_ptr

#include "requests_api.hpp" // api

namespace ilrd
{

RequestArgs::RequestArgs(boost::shared_ptr<char[]> buf_, u_int64_t from_)
    : m_buf(buf_), m_from(from_)
{}

RequestHandler::RequestHandler(boost::shared_ptr<RequestArgs> args_)
    : m_args(args_)
{}

RequestHandler::~RequestHandler()
{}

boost::shared_ptr<RequestArgs> RequestHandler::GetArgs()
{
    return m_args;
}

}