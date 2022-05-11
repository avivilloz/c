/*****************************************************************************
Title: plug_and_play - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: plug_and_play
******************************************************************************/

#include "plug_and_play.hpp" // api
#include "handleton.hpp" // Handleton
#include "runtime_config.hpp" // RuntimeConfig

namespace ilrd
{

const std::string PlugAndPlay::s_dllsDir = GetDllsDir();

PlugAndPlay::PlugAndPlay()
    : m_monitor(s_dllsDir), m_loader()
{
    m_monitor.Register(m_loader.GetCallbackBase().get());
}

std::string PlugAndPlay::GetDllsDir()
{
    Handleton<RuntimeConfig> config;
    return config->GetValue(DLLS_DIR);
}

}

/*****************************************************************************/

