/*****************************************************************************
Title: input_proxy - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: input_proxy
******************************************************************************/

#ifndef ILRD_OL91_INPUT_PROXY_HPP
#define ILRD_OL91_INPUT_PROXY_HPP

#include <boost/shared_ptr.hpp>

namespace ilrd
{

class InputProxy
{
public:
    virtual ~InputProxy() = 0;

    class Task
    {
    public:
        virtual ~Task() = 0;
        virtual void operator()() = 0;
    };

    virtual boost::shared_ptr<Task> GetTask() = 0;
};

}

#endif /*ILRD_OL91_INPUT_PROXY_HPP*/

/*****************************************************************************/
