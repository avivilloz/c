/*****************************************************************************
Title: reactor - Infinity Labs R&D 
Group: OL91
Description: reactor API
******************************************************************************/

#ifndef ILRD_RD91_REACTOR_HPP
#define ILRD_RD91_REACTOR_HPP

#include <map>
#include <queue>
#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include <sys/types.h>

namespace ilrd
{

class Reactor : private boost::noncopyable
{
public:
    explicit Reactor();
    ~Reactor();

    void Run();
    void Stop();

    enum EventType {READ, WRITE, EXCEPTION, NUM_OF_SETS};

    typedef boost::function<void()> Handler_t;
    typedef std::pair<int, EventType> Key_t;

    void Register(int fd, Handler_t handler, EventType operation);
    void Unregister(int fd, EventType operation);

private:
    class Demultiplexer : boost::noncopyable
    {
    public:
        Demultiplexer();
        void Select(std::queue<Key_t> &events);
        void AddFd(int fd, EventType operation);
        void RemoveFd(int fd, EventType operation);
        
    private:
        fd_set m_sets[NUM_OF_SETS];
    };

    std::map<Key_t, Handler_t> m_handlers;
    Demultiplexer m_demultiplexer;
    bool m_shouldRun;
};

} // namespace ilrd

#endif // ILRD_RD91_REACTOR_HPP

/*****************************************************************************/
