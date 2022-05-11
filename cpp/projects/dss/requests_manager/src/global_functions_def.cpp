/*****************************************************************************
Title: global_funcs_def - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
description: global_funcs_def
******************************************************************************/

#include <boost/shared_ptr.hpp> // boost::shared_ptr

#include "global_functions_def.hpp" // api
#include "global_functions.hpp" // Write_t, Read_t
#include "requests_api.hpp" // RequestHandler
#include "requests_manager.hpp" // RequestsManager
#include "handleton.hpp" // Handleton

namespace ilrd
{

void Write(boost::shared_ptr<RequestHandler> request)
{
    Handleton<RequestsManager> requestsManager;
    requestsManager->Write(request);
}

void Read(boost::shared_ptr<RequestHandler> request)
{
    Handleton<RequestsManager> requestsManager;
    requestsManager->Read(request);
}

extern Write_t g_write;
extern Read_t g_read;

void __attribute__((constructor)) init()
{
    g_write = Write;
    g_read = Read;
}

}
