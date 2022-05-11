/*****************************************************************************
Title: helper - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: helper
******************************************************************************/

#ifndef ILRD_OL91_HELPER_HPP
#define ILRD_OL91_HELPER_HPP

template<typename ExceptionType>
inline void ThrowIfBad(bool isBad, const char *msg)
{
    if (isBad)
    {
        throw ExceptionType(msg);
    }
}

#endif /*ILRD_OL91_HELPER_HPP*/

/*****************************************************************************/
