/*****************************************************************************
Title: scope_lock - Infinity Labs R&D 
Group: OL91
Description: scope_lock API
******************************************************************************/

#ifndef ILRD_OL91_SCOPE_LOCK_HPP
#define ILRD_OL91_SCOPE_LOCK_HPP

#include <boost/core/noncopyable.hpp>
#include <pthread.h>

/*****************************************************************************/

namespace ilrd
{
template<class T>
class ScopeLock : private boost::noncopyable
{
public:
    explicit ScopeLock(T& lock);
    ~ScopeLock();
private:
    T& m_lock;
};

template<class T> ScopeLock<T>::ScopeLock(T &lock)
    : m_lock(lock)
{
    m_lock.lock();
}

template<class T> ScopeLock<T>::~ScopeLock()
{
    m_lock.unlock();
}

template<>
ScopeLock<pthread_mutex_t>::ScopeLock(pthread_mutex_t &lock)
    : m_lock(lock)
{
    pthread_mutex_lock(&m_lock);
}

template<>
ScopeLock<pthread_mutex_t>::~ScopeLock()
{
    pthread_mutex_unlock(&m_lock);
}
}

/*****************************************************************************/

#endif // ILRD_OL91_SCOPE_LOCK_HPP

