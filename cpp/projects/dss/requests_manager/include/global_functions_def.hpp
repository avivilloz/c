/*****************************************************************************
Title: global_funcs_def - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
description: global_funcs_def
******************************************************************************/

#ifndef ILRD_OL91_GLOBAL_FUNCTIONS_DEF_HPP
#define ILRD_OL91_GLOBAL_FUNCTIONS_DEF_HPP

#include <boost/shared_ptr.hpp> // boost::shared_ptr

#include "requests_api.hpp" // RequestHandler

namespace ilrd
{

void Read(boost::shared_ptr<RequestHandler> request);
void Write(boost::shared_ptr<RequestHandler> request);

void __attribute__((constructor)) init();

}

#endif /*ILRD_OL91_GLOBAL_FUNCTIONS_DEF_HPP*/
