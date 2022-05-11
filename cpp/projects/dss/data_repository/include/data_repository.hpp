/*****************************************************************************
Title: data_repository - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: data_repository
******************************************************************************/

#ifndef ILRD_OL91_DATA_REPOSITORY_HPP
#define ILRD_OL91_DATA_REPOSITORY_HPP

#include <sys/types.h> // u_int32_t
#include <map> // std::map
#include <vector> // std::vector
#include <boost/thread/mutex.hpp> // boost::mutex
#include <utility> // std::pair

#include "handleton.hpp" // Handleton
#include "minion_proxy.hpp" // MinionProxy

namespace ilrd
{


class DataRepository
{
public:
    void Register(u_int64_t from);

    enum StorageType {MAIN, BACKUP};

    bool Write(const char *buf, u_int64_t from, StorageType st);
    bool Read(char *buf, u_int64_t from, StorageType st);

private:
    typedef std::pair<u_int64_t, StorageType> FilesMapKey_t;

    std::vector<MinionProxy> m_minions;
    std::map<FilesMapKey_t, std::size_t> m_files;
    std::size_t m_currMinion;

    friend class Handleton<DataRepository>;
    DataRepository();

    std::string GetMinionPath(std::size_t i);
    std::size_t GetMinion();
};

}

#endif /*ILRD_OL91_DATA_REPOSITORY_HPP*/
