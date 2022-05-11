/*****************************************************************************
Title: logger - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: 
Description: logger API
******************************************************************************/

#include <string.h> // strerror
#include <errno.h> // errno

#include "logger.hpp" // api 
#include "helper.hpp" // ThrowIfBad

/*****************************************************************************/

namespace ilrd
{

Logger::~Logger()
{
    int status = close(m_fd);
    ThrowIfBad<std::runtime_error>(status == -1, strerror(errno));
}

class LogMsg
{
public:
    LogMsg(int fd, const std::string& content)
        : m_fd(fd), m_content(content)
    {}
    void operator()()
    {
        ssize_t nBytesRead = write(m_fd, m_content.c_str(), m_content.size());
        ThrowIfBad<std::runtime_error>(-1 == nBytesRead, strerror(errno));
    }
private:
    int m_fd;
    const std::string &m_content;
};

void Logger::Log(const std::string& content)
{
    boost::shared_ptr<ThreadPool::Task> task(
            new ThreadPool::RegularTask<LogMsg>(LogMsg(m_fd, content), 0));
    m_thread_pool.Add(task);
}

Logger::Logger()
    : m_fd(open(FILE_TO_LOG, O_CREAT | O_WRONLY | O_APPEND, 0777)), 
    m_thread_pool(NUM_OF_THREADS)
{
    ThrowIfBad<std::runtime_error>(-1 == m_fd, strerror(errno)); 
}

}

/*****************************************************************************/
