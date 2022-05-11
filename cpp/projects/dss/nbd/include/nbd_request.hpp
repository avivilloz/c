/*****************************************************************************
Title: nbd_action_manager - Infinity Labs R&D 
Group: OL91
Description: nbd_action_manager
******************************************************************************/

#ifndef ILRD_OL91_NBD_ACTION_MANAGER_HPP
#define ILRD_OL91_NBD_ACTION_MANAGER_HPP

#include <boost/shared_ptr.hpp> // boost::shared_ptr

#include "nbd_reply.hpp" // NBDReply
#include "requests_api.hpp" // RequestArgs, RequestHandler

namespace ilrd
{

class NBDRequestHandler : public RequestHandler
{
public:
    NBDRequestHandler(
        boost::shared_ptr<RequestArgs> args_,
        boost::shared_ptr<ReplyHandler> reply_
    );
    boost::shared_ptr<RequestArgs> GetArgs();
    void Reply(bool status);
    
private:
    boost::shared_ptr<ReplyHandler> m_reply;
    bool m_replied;
};

}

#endif /*ILRD_OL91_NBD_ACTION_MANAGER_HPP*/
