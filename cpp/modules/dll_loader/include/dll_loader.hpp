/*****************************************************************************
Title: dll_loader - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: dll_loader
******************************************************************************/

#ifndef ILRD_RD91_DLL_LOADER_HPP
#define ILRD_RD91_DLL_LOADER_HPP

#include <string>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include "dispatcher.hpp"

namespace ilrd
{

class DllLoader : private boost::noncopyable
{
public:
    DllLoader();

    boost::shared_ptr<CallbackBase<std::string> > GetCallbackBase() const;
    
private:
    boost::shared_ptr<CallbackBase<std::string> > m_callback;

    void LoadSO(const std::string filename);
};

} // namespace ilrd

#endif // ILRD_RD91_DLL_LOADER_HPP
