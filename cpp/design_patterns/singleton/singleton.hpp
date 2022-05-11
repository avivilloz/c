/*****************************************************************************
* title: singleton
* author: aviv illoz
* description: singleton api
******************************************************************************/

#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <boost/core/noncopyable.hpp>
#include <boost/thread/mutex.hpp>

namespace avivilloz
{

template <class T>
class Singleton : private boost::noncopyable
{
public:
    static T *GetInstance();
private:
    static boost::mutex s_mutex;
    static T *s_pInstance;
    static void CleanUp();
    Singleton();
};

#include "singleton_templ.hpp"

}

#endif // SINGLETON_HPP
