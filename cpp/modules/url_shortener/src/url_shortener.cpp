/****************************************************************************
 * Title: Url Shortener
 * Author: Aviv Illoz
 * Description: Provides api for url shortener
****************************************************************************/

#include <fstream> //std::fstream
#include <vector> // std::vector
#include <string> // std::string
#include <algorithm> // std::reverse
#include <boost/thread/mutex.hpp> // boost::mutex::scoped_lock

#include "url_shortener.hpp" // api
#include "runtime_config.hpp" // RuntimeConfig
#include "singleton.hpp" // Singleton

namespace avivilloz
{

Storage::Storage(std::string pathToStorage)
    : m_file(pathToStorage.c_str(), std::ios::in | std::ios::out | std::ios::app)
{}

void Storage::Append(std::string url)
{
    m_file << url << std::endl;
}

void Storage::ReadAll(std::vector<std::string> &urls)
{
    std::string str;

    while (std::getline(m_file, str)) 
    {
        urls.push_back(str);
    }

    m_file.clear();
}

const std::string UrlShortener::s_pathToStorage(GetPathToStorage());
const std::string UrlShortener::s_rawUrl(GetRawUrl());
const std::string UrlShortener::s_charsMap( 
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"); 
const std::size_t UrlShortener::s_base = s_charsMap.length();

UrlShortener::UrlShortener()
    : m_storage(s_pathToStorage), m_urls(), m_counter(0), m_mutex()
{
    m_storage.ReadAll(m_urls);
    m_counter = m_urls.size();
}

std::string UrlShortener::GetShortUrl(std::string url)
{
    std::string urlOffset; 
    std::size_t id = 0;
    bool urlExists = 0;

    for (std::size_t i = 0; i < m_urls.size(); ++i)
    {
        if (m_urls[i] == url)
        {
            urlExists = 1;
            id = i;   
            break;
        }
    }

    if (!urlExists)
    {
        boost::mutex::scoped_lock lock(m_mutex);
        id = m_counter++;
        m_urls.push_back(url);
        m_storage.Append(url);
    }

    for (; 0 != id; id /= s_base) 
    { 
        urlOffset.push_back(s_charsMap[id % s_base]);
    } 

    urlOffset.push_back(s_charsMap[id % s_base]);

    std::reverse(urlOffset.begin(), urlOffset.end());

    return s_rawUrl + urlOffset;
}

std::string UrlShortener::GetUrl(std::string shortUrl)
{
    std::string urlOffset(&shortUrl.c_str()[s_rawUrl.length()]);

    return m_urls[GetId(urlOffset)];
}

std::size_t UrlShortener::GetId(std::string urlOffset)
{
    std::size_t id = 0;
    std::size_t len = urlOffset.length();

    for (std::size_t i = 0; i < len; ++i)
    {
        char c = urlOffset[i];

        if ('a' <= c && c <= 'z')
        {
            id = id * s_base + c - 'a';
        }
        else if ('A' <= c && c <= 'Z')
        {
            id = id * s_base + c - 'A' + 26;
        }
        else if ('0' <= c && c <= '9')
        {
            id = id * s_base + c - '0' + 52;
        }
    }

    return id;
}

std::string UrlShortener::GetPathToStorage()
{
    RuntimeConfig *config = Singleton<RuntimeConfig>::GetInstance();
    return config->GetValue(PATH_TO_URLS_STORAGE_FILE);
}

std::string UrlShortener::GetRawUrl()
{
    RuntimeConfig *config = Singleton<RuntimeConfig>::GetInstance();
    return config->GetValue(RAW_URL);
}

}
