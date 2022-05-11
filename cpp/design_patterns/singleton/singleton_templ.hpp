/*****************************************************************************
* title: singleton_templ
* author: aviv illoz
* description: singleton_templ
******************************************************************************/

#include <stdlib.h>

#include "singleton.hpp" // api

template<class T>
T *Singleton<T>::s_pInstance = NULL;

template<class T>
boost::mutex Singleton<T>::s_mutex;

template<class T>
T* Singleton<T>::GetInstance()
{
    if (NULL == s_pInstance)
    {
        boost::mutex::scoped_lock lock(s_mutex);
        if (NULL == s_pInstance)
        {
            s_pInstance = new T;

            if (0 != atexit(CleanUp))
            {
                delete s_pInstance;
                throw std::runtime_error("GetInstance: atexit failed");
            }
        } 
    }

    if (reinterpret_cast<T*>(0xDEADBEEF) == s_pInstance)
    {
        throw std::runtime_error("GetInstance: instance already destroyed");
    }

    return s_pInstance;
}

template<class T>
void Singleton<T>::CleanUp()
{
    delete s_pInstance;
    s_pInstance = reinterpret_cast<T*>(0xDEADBEEF);
}