/*****************************************************************************
Title: commands - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: commands
******************************************************************************/

#include <linux/nbd.h> // nbd flags

#include "commands.hpp" // api
#include "commands_api.hpp" // CommandCreator
#include "write.hpp" // Write
#include "read.hpp" // Read
#include "trim.hpp" // Trim
#include "flush.hpp" // Flush
#include "disc.hpp" // Disc
#include "framework.hpp" // Framework
#include "handleton.hpp" // Handleton

namespace ilrd
{

void __attribute__((constructor)) init()
{
    Handleton<Framework> framework;
    framework->Add(NBD_CMD_READ, CommandCreator<Read>);
    framework->Add(NBD_CMD_WRITE, CommandCreator<Write>);
    framework->Add(NBD_CMD_TRIM, CommandCreator<Trim>);
    framework->Add(NBD_CMD_FLUSH, CommandCreator<Flush>);
    framework->Add(NBD_CMD_DISC, CommandCreator<Disc>);
}

}
