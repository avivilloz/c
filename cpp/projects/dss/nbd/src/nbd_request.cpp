/*****************************************************************************
Title: nbd_action_manager - Infinity Labs R&D 
Group: OL91
Description: nbd_action_manager
******************************************************************************/

#include <boost/shared_ptr.hpp> // boost::shared_ptr

#include "nbd_request.hpp" // api
#include "nbd_reply.hpp" // NBDReply
#include "requests_api.hpp" // RequestHandler

namespace ilrd
{

NBDRequestHandler::NBDRequestHandler(
    boost::shared_ptr<RequestArgs> args_,
    boost::shared_ptr<ReplyHandler> reply_
)
    : RequestHandler(args_), m_reply(reply_), m_replied(0)
{}

void NBDRequestHandler::Reply(bool status)
{
    if (!m_replied)
    {
        (*m_reply)(status);
        m_replied = 1;
    }
}

}
