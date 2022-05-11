/*****************************************************************************
Title: nbd_reply - Infinity Labs R&D 
Group: OL91
Description: nbd_reply
******************************************************************************/

#include <linux/nbd.h> // struct nbd_reply
#include <sys/types.h> // u_int32_t
#include <boost/thread/mutex.hpp> // boost::mutex
#include <boost/shared_ptr.hpp> // boost::shared_ptr

#include "socket_manager.hpp" // SocketManager
#include "nbd_reply.hpp" // api

namespace ilrd
{

ReplyHandler::ReplyHandler(SocketManager &skM_, struct nbd_reply reply_)
    : m_skM(skM_), m_reply(reply_)
{}

ReplyHandler::~ReplyHandler()
{}

void ReplyHandler::operator()(bool status)
{
    m_reply.error = status;
    m_skM.Write(reinterpret_cast<char*>(&m_reply), sizeof(struct nbd_reply));
}

ReadReplyHandler::ReadReplyHandler(
    SocketManager &skM_, 
    struct nbd_reply reply_,
    boost::shared_ptr<char[]> buf_,
    u_int32_t len_
)
    : ReplyHandler(skM_, reply_), m_skM(skM_), m_buf(buf_), m_len(len_)
{}

void ReadReplyHandler::operator()(bool status)
{
    ReplyHandler::operator()(status);
    m_skM.Write(m_buf.get(), m_len);
}

}
