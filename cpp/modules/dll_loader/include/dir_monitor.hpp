/*****************************************************************************
Title: dir_monitor - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: dir_monitor
******************************************************************************/

#ifndef ILRD_RD91_DIR_MONITOR_HPP
#define ILRD_RD91_DIR_MONITOR_HPP

#include <string>
#include <boost/thread.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include "dispatcher.hpp"

namespace ilrd
{

class DirMonitor : private boost::noncopyable
{
public:
    explicit DirMonitor(const std::string &path);

    void Register(
        CallbackBase<std::string> *callback
    );

private:
    const std::string& m_path;
    Dispatcher<std::string> m_dispatcher;
    boost::thread m_thread;

    void Monitor();
};

} // namespace ilrd

#endif // ILRD_RD91_DIR_MONITOR_HPP
