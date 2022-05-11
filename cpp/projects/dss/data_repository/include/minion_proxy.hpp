/*****************************************************************************
Title: minion_proxy - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: minion_proxy
******************************************************************************/

#ifndef ILRD_OL91_MINION_PROXY_HPP
#define ILRD_OL91_MINION_PROXY_HPP

#include <sys/types.h> // u_int32_t, u_int64_t
#include <string> // std::string

namespace ilrd
{

class MinionProxy
{
public:
    MinionProxy(std::string storagePath_);
    bool Read(char *buf, u_int64_t from);
    bool Write(const char *buf, u_int64_t from);

private:
    std::string m_storagePath;
};

}

#endif /*ILRD_OL91_MINION_PROXY_HPP*/
