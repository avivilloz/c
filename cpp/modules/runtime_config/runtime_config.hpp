/*****************************************************************************
* title: runtime configuration
* author: aviv illoz
* description: runtime configuration API
******************************************************************************/

#ifndef RUNTIME_CONFIG_HPP
#define RUNTIME_CONFIG_HPP

#include <string> // std::string
#include <map> // std::map

#include "singleton.hpp" // Handleton

namespace avivilloz
{

class RuntimeConfig
{
public:
    std::string GetValue(std::string keyParam_);

private:
    friend class Singleton<RuntimeConfig>;

    static const std::string s_regex;
    static const std::string s_configFile;
    std::map<std::string, std::string> m_configParams;
    
    RuntimeConfig();
};

}

#endif // RUNTIME_CONFIG_HPP
