/*****************************************************************************
Title: handleton - Infinity Labs R&D 
Group: OL91
Description: handleton API
******************************************************************************/

#ifndef ILRD_RD91_HANDLETON_HPP
#define ILRD_RD91_HANDLETON_HPP

#include <boost/core/noncopyable.hpp> // boost::noncopyable
#include <boost/thread/mutex.hpp> // boost::mutex

namespace ilrd
{

template<class T>
class Handleton : private boost::noncopyable
{
public:
    Handleton();
    operator T&();
    operator const T&() const;
    T *operator->();
    const T *operator->() const;
    T *Get();

private:
    static boost::mutex s_mutex;
    static T *s_pInstance;
    static T* GetInstance();
    static void CleanUp();
};

#ifndef EXECUTABLE
#include "handleton_impl.hpp"
#endif // EXECUTABLE

#define HANDLETON_INSTANTIATE(T) template class Handleton<T>;

}

#endif // ILRD_RD91_HANDLETON_HPP
