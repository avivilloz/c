/*****************************************************************************
Title: handleton - Infinity Labs R&D 
Group: OL91
Description: handleton API
******************************************************************************/

#include <stdlib.h> // atexit
#include <boost/thread/mutex.hpp> // boost::mutex::scoped_lock

#include "handleton.hpp" // api
#include "helper.hpp" // ThrowIfBad

template<class T>
T *Handleton<T>::s_pInstance;

template<class T>
boost::mutex Handleton<T>::s_mutex;

template<class T>
Handleton<T>::Handleton() 
{ 
    GetInstance();
}

template<class T>
Handleton<T>::operator T&() 
{ 
    return *s_pInstance;
}

template<class T>
Handleton<T>::operator const T&() const 
{ 
    return *s_pInstance;
} 

template<class T>
T *Handleton<T>::operator->()
{ 
    return s_pInstance;
}

template<class T>
const T *Handleton<T>::operator->() const 
{ 
    return s_pInstance;
}

template<class T>
T* Handleton<T>::GetInstance()
{
    if (NULL == s_pInstance)
    {
        boost::mutex::scoped_lock lock(s_mutex); 
        if (NULL == s_pInstance)
        {
            ThrowIfBad<std::runtime_error>(0 != atexit(CleanUp), 
                    "GetInstance: atexit failed");

            s_pInstance = new T;
        } 
    }

    return s_pInstance;
}

template<class T>
void Handleton<T>::CleanUp()
{
    delete s_pInstance;
    s_pInstance = NULL;
}
