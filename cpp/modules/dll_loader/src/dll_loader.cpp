/*****************************************************************************
Title: dll - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: 
Description: dll API
******************************************************************************/

#include <iostream> // cerr
#include <dlfcn.h> // dlopen

#include "dll_loader.hpp" // api 
#include "dispatcher.hpp" // Callback
#include "helper.hpp" // ThrowIfBad

namespace ilrd
{

DllLoader::DllLoader()
    : m_callback(new Callback<std::string, DllLoader>(
        *this, &DllLoader::LoadSO))
{}

boost::shared_ptr<CallbackBase<std::string> > 
DllLoader::GetCallbackBase() const
{
    return m_callback;
}
    
void DllLoader::LoadSO(const std::string filename)
{
    if (0 == strcmp(&filename.c_str()[filename.size() - 3], ".so"))
    {
        void *handle = dlopen(filename.c_str(), RTLD_LAZY);
        ThrowIfBad<std::runtime_error>(NULL == handle, dlerror());
    }
}

}
