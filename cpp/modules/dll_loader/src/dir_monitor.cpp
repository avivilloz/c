/*****************************************************************************
Title: dir_monitor - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: dir_monitor
******************************************************************************/

#include <iostream> // cerr
#include <cerrno> // strerr
#include <boost/bind.hpp> // bind
#include <sys/inotify.h> // inotify functions
#include <exception> // exceptions

#include "dir_monitor.hpp" // api
#include "dispatcher.hpp" // Dispatcher, CallbackBase
#include "helper.hpp" // ThrowIfBad

namespace ilrd
{
#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUFF_LEN (1024 * (EVENT_SIZE + 16))

DirMonitor::DirMonitor(const std::string &path)
    : m_path(path), m_dispatcher(),
    m_thread(boost::bind(&DirMonitor::Monitor, this))
{}

void DirMonitor::Register(
    CallbackBase<std::string> *callback
)
{
    m_dispatcher.Register(callback);
}

void DirMonitor::Monitor()
{
    int fd = inotify_init();
    ThrowIfBad<std::runtime_error>(-1 == fd, strerror(errno));
    int wd = inotify_add_watch(fd, m_path.c_str(), IN_CLOSE_WRITE | IN_MOVED_TO);
    ThrowIfBad<std::runtime_error>(-1 == wd, strerror(errno));

    char events[BUFF_LEN];

    while (1)
    {
        ssize_t nBytesRead = read(fd, events, BUFF_LEN);
        ThrowIfBad<std::runtime_error>(-1 == nBytesRead, strerror(errno));

        char *curr = events;
        char *end = &events[nBytesRead];
        struct inotify_event *event = NULL;

        for (; curr != end; curr += (EVENT_SIZE + event->len))
        {
            event = (struct inotify_event *)curr;
            m_dispatcher.Dispatch(m_path + event->name); 
        }
    }

    int status = inotify_rm_watch(fd, wd);
    ThrowIfBad<std::runtime_error>(-1 == status, strerror(errno));
    status = close(fd);
    ThrowIfBad<std::runtime_error>(-1 == status, strerror(errno));
}

}

/*****************************************************************************/

