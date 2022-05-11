/*****************************************************************************
* title: runtime configuration
* author: aviv illoz
* description: runtime configuration API
******************************************************************************/

#include <string> // std::string
#include <map> // std::map
#include <fstream> // std::ifstream
#include <stdexcept> // std::runtime_error
#include <boost/regex.hpp> // boost::regex, boost::smatch, boost::regex_search

#include "runtime_config.hpp" // api
#include "utils.hpp" // ThrowIfBad

namespace avivilloz
{

const std::string RuntimeConfig::s_regex = REGEX;
const std::string RuntimeConfig::s_configFile = CONFIG_FILE;

RuntimeConfig::RuntimeConfig()
    : m_configParams()
{
    std::ifstream file(s_configFile.c_str());
    ThrowIfBad<std::runtime_error>(file.fail(), "failed to open config file");

    boost::regex regEx(s_regex);
    std::string expression;

    while (std::getline(file, expression))
    {
        boost::smatch result;
        if (boost::regex_search(expression, result, regEx))
        {
            m_configParams[result[1]] = result[2];
        }
    }
}

std::string RuntimeConfig::GetValue(std::string keyParam_)
{
    return m_configParams[keyParam_];
}

}
