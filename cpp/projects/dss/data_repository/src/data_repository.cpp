/*****************************************************************************
Title: data_repository - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: data_repository
******************************************************************************/

#include <sys/types.h> // u_int32_t
#include <boost/thread/mutex.hpp> // boost::mutex::scoped_lock
#include <utility> // std::make_pair
#include <map> // std::map<>::iterator
#include <string> // std::string
#include <sstream> // std::stringstream
#include <utility> // std::pair
#include <stdexcept> // std::invalid_argument

#include "data_repository.hpp" // api
#include "minion_proxy.hpp" // MinionProxy
#include "handleton.hpp" // Handleton
#include "runtime_config.hpp" // RuntimeConfig
#include "helper.hpp" // ThrowIfBad

namespace ilrd
{

DataRepository::DataRepository()
    : m_minions(), m_files(), m_currMinion(0)
{
    std::string minionPath;

    std::size_t i = 0;
    for (; "" != (minionPath = GetMinionPath(i)); ++i)
    {
        m_minions.push_back(minionPath);
    };

    ThrowIfBad<std::invalid_argument>(i < 2, "not enough minions");
}

void DataRepository::Register(u_int64_t from)
{
    FilesMapKey_t mainKey(from, StorageType(MAIN));
    FilesMapKey_t backupKey(from, StorageType(BACKUP));

    std::map<FilesMapKey_t, std::size_t>::iterator it = m_files.find(mainKey);
    if (it == m_files.end())
    {
        m_files[mainKey] = GetMinion();
    }

    it = m_files.find(backupKey);
    if (it == m_files.end())
    {
        m_files[backupKey] = GetMinion();
    }
}

bool DataRepository::Write(const char *buf, u_int64_t from, StorageType st)
{
    return m_minions[m_files[FilesMapKey_t(from, st)]].Write(buf, from);
}

bool DataRepository::Read(char *buf, u_int64_t from, StorageType st)
{
    return m_minions[m_files[FilesMapKey_t(from, st)]].Read(buf, from);
}

std::string DataRepository::GetMinionPath(std::size_t i)
{
    std::stringstream ss;
    ss << MINION << i;

    Handleton<RuntimeConfig> config;
    return config->GetValue(ss.str());
}

std::size_t DataRepository::GetMinion()
{
    std::size_t minion = m_currMinion;

    m_currMinion = (m_currMinion + 1) % m_minions.size();

    return minion;
}

}
