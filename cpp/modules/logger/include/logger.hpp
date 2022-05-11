/*****************************************************************************
Title: logger - Infinity Labs R&D 
Group: OL91
Description: logger API
******************************************************************************/

#ifndef ILRD_RD91__HPP
#define ILRD_RD91__HPP

#include <boost/noncopyable.hpp>

#include "singleton.hpp"
#include "thread_pool.hpp"

namespace ilrd
{
#define FILE_TO_LOG "/tmp/log.txt"
#define NUM_OF_THREADS 12

class Logger : boost::noncopyable
{
public:
    ~Logger();
    void Log(const std::string& content);

private:
    int m_fd;
    ThreadPool m_thread_pool;

    friend class Singleton<Logger>;
    Logger();
};

} // namespace ilrd

#endif // ILRD_RD91__HPP

/*****************************************************************************/
