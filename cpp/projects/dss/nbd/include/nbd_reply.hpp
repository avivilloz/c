/*****************************************************************************
Title: nbd_reply - Infinity Labs R&D 
Group: OL91
Description: nbd_reply
******************************************************************************/

#ifndef ILRD_OL91_NBD_REPLY_HPP
#define ILRD_OL91_NBD_REPLY_HPP

#include <linux/nbd.h> // struct nbd_reply
#include <sys/types.h> // u_int32_t
#include <boost/thread/mutex.hpp> // boost::mutex
#include <boost/shared_ptr.hpp> // boost::shared_ptr

#include "socket_manager.hpp" // SocketManager

namespace ilrd
{

class ReplyHandler
{
public:
    ReplyHandler(SocketManager &skM_, struct nbd_reply reply_);
    virtual ~ReplyHandler();
    virtual void operator()(bool status);

private:
    SocketManager &m_skM;
    struct nbd_reply m_reply;
};

class ReadReplyHandler : public ReplyHandler
{
public:
    ReadReplyHandler(
        SocketManager &skM_, 
        struct nbd_reply reply_,
        boost::shared_ptr<char[]> buf_,
        u_int32_t len_
    );
    void operator()(bool status);

private:
    SocketManager &m_skM;
    boost::shared_ptr<char[]> m_buf;
    u_int32_t m_len;
};

}

#endif /*ILRD_OL91_NBD_REPLY_HPP*/
