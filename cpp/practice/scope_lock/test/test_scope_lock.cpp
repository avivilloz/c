/*****************************************************************************
Title: scope_lock - Infinity Labs R&D 
Group: OL91
Author: Aviv
Description: scope_lock test
******************************************************************************/

#include <iostream> // cout
#include <boost/thread/mutex.hpp>

#include "scope_lock.hpp" // api

using namespace ilrd;

/*****************************************************************************/

int main()
{
    pthread_mutex_t c_mutex = PTHREAD_MUTEX_INITIALIZER; 
    ScopeLock<pthread_mutex_t> l1(c_mutex);

    boost::mutex cpp_mutex;
    ScopeLock<boost::mutex> l2(cpp_mutex);

    return 0;
}

/*****************************************************************************/

