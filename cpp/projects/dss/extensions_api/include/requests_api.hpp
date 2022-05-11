/*****************************************************************************
Title: requests api - Infinity Labs R&D 
Group: OL91
Author: Aviv
Description: any command plugin needs to derive or use classes from this api.
******************************************************************************/

#ifndef ILRD_RD91_REQUESTS_API_HPP
#define ILRD_RD91_REQUESTS_API_HPP

#include <sys/types.h> // u_int32_t, u_int64_t 
#include <boost/shared_ptr.hpp> // boost::shared_ptr

namespace ilrd
{

struct RequestArgs
{
    RequestArgs(boost::shared_ptr<char[]> buf_, u_int64_t from_);
    boost::shared_ptr<char[]> m_buf;
    u_int64_t m_from;
};

class RequestHandler
{
public:
    RequestHandler(boost::shared_ptr<RequestArgs> args_);
    virtual ~RequestHandler() = 0;
    virtual void Reply(bool status) = 0;
    boost::shared_ptr<RequestArgs> GetArgs();

private:
    boost::shared_ptr<RequestArgs> m_args;
};

}

#endif // ILRD_RD91_REQUESTS_API_HPP