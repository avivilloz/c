/*****************************************************************************
Title: minion_proxy - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: minion_proxy
******************************************************************************/

#include <sys/types.h> // u_int32_t, u_int64_t
#include <boost/lexical_cast.hpp> // boost::lexical_cast
#include <fstream> // std::fstream
#include <string> // std::string
#include <sstream> // std::stringstream
#include <iostream> 

#include "minion_proxy.hpp" // api

namespace ilrd
{

MinionProxy::MinionProxy(std::string storagePath_)
    : m_storagePath(storagePath_)
{}

bool MinionProxy::Read(char *buf, u_int64_t offset)
{
    std::stringstream filePath;
    filePath << m_storagePath << offset;

    std::cout << "in minion proxy read" << std::endl;

    std::ifstream file(filePath.str().c_str());
    if (file.fail())
    {
        std::cout << "in minion proxy read failed" << std::endl;
        return 1;
    }
    else
    {
        file >> buf;
        std::cout << "in minion proxy read succeded" << std::endl;
    }

    return 0;
}

bool MinionProxy::Write(const char *buf, u_int64_t offset)
{
    std::stringstream filePath;
    filePath << m_storagePath << offset;

    std::ofstream file(filePath.str().c_str());
    if (file.fail())
    {
        return 1;
    }

    file << buf; 

    return 0;
}

}
