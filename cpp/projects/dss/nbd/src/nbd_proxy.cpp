/*****************************************************************************
Title: nbd_proxy - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: nbd_proxy
******************************************************************************/

#include <string.h> // memcpy
#include <sys/types.h> // u_int64_t, u_int32_t
#include <arpa/inet.h> // ntohl, htonl
#include <linux/nbd.h> // nbd_reply, nbd_request
#include <boost/thread/mutex.hpp> // boost::mutex, boost::mutex::scoped_lock

#include "nbd_proxy.hpp" // api
#include "nbd_task.hpp" // NBDTask
#include "nbd_reply.hpp" // ReplyHandler, ReadReplyHandler
#include "nbd_request.hpp" // NBDRequestHandler
#include "requests_api.hpp" // RequestHandler, RequestArgs
#include "input_proxy.hpp" // InputProxy::Task

/*****************************************************************************/

namespace ilrd
{

#ifdef WORDS_BIGENDIAN
static u_int64_t ntohll(u_int64_t a) 
{
    return a;
}
#else
static u_int64_t ntohll(u_int64_t a) 
{
    u_int32_t lo = a & 0xffffffff;
    u_int32_t hi = a >> 32U;
    lo = ntohl(lo);
    hi = ntohl(hi);
    return ((u_int64_t) lo) << 32U | hi;
}
#endif
#define htonll ntohll

NBDProxy::NBDProxy(int sk_) 
    : m_skM(sk_), m_mutex()
{}

boost::shared_ptr<InputProxy::Task> NBDProxy::GetTask()
{
    struct nbd_request nbdRequest;
    struct nbd_reply nbdReply;

    m_skM.Read((char *)&nbdRequest, sizeof(nbdRequest)); 

    memcpy(nbdReply.handle, nbdRequest.handle, sizeof(nbdReply.handle));
    nbdReply.magic = htonl(NBD_REPLY_MAGIC);
    nbdReply.error = htonl(0);

    u_int32_t len = ntohl(nbdRequest.len);
    u_int32_t type = ntohl(nbdRequest.type);
    u_int64_t from = ntohll(nbdRequest.from);

    boost::shared_ptr<char[]> buf(new char[len]);

    if (NBD_CMD_WRITE == type)
    {
        m_skM.Read(buf.get(), len);
    }

    RequestArgs *args(new RequestArgs(buf, from));
    ReplyHandler *reply = NULL;

    if (NBD_CMD_READ == type)
    {
        reply = new ReadReplyHandler(m_skM, nbdReply, buf, len);
    }
    else
    {
        reply = new ReplyHandler(m_skM, nbdReply);
    }

    boost::shared_ptr<RequestHandler> request(
        new NBDRequestHandler(
            boost::shared_ptr<RequestArgs>(args),
            boost::shared_ptr<ReplyHandler>(reply)
        )
    );

    NBDTask *task(new NBDTask(type, request, m_mutex));

    return boost::shared_ptr<InputProxy::Task>(task);
}

}

/*****************************************************************************/

