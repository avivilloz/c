/*****************************************************************************
Title: global_functions - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
description: global_funcs_def
******************************************************************************/

#ifndef ILRD_OL91_GLOBAL_FUNCTIONS_HPP
#define ILRD_OL91_GLOBAL_FUNCTIONS_HPP

#include <boost/shared_ptr.hpp> // boost::shared_ptr

#include "requests_api.hpp" // RequestHandler

namespace ilrd
{

typedef void (*Write_t)(boost::shared_ptr<RequestHandler>);
typedef void (*Read_t)(boost::shared_ptr<RequestHandler>);

}

#endif /*ILRD_OL91_GLOBAL_FUNCTIONS_HPP*/
