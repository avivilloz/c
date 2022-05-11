/*****************************************************************************
Title: plug_and_play - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: plug_and_play
******************************************************************************/

#ifndef ILRD_OL91_PLUG_AND_PLAY_HPP
#define ILRD_OL91_PLUG_AND_PLAY_HPP

#include <string> // std::string

#include "dll_loader.hpp" // DllLoader
#include "dir_monitor.hpp" // DirMonitor

namespace ilrd
{

class PlugAndPlay
{
public:
    PlugAndPlay();

private:
    DirMonitor m_monitor;
    DllLoader m_loader;
    static const std::string s_dllsDir;

    static std::string GetDllsDir();
};

}

#endif /*ILRD_OL91_PLUG_AND_PLAY_HPP*/

/*****************************************************************************/
