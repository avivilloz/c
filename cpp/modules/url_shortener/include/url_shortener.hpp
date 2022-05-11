/****************************************************************************
 * Title: Url Shortener
 * Author: Aviv Illoz
 * Description: Provides api for url shortener
****************************************************************************/

#ifndef URL_SHORTENER_HPP
#define URL_SHORTENER_HPP

#include <fstream> //std::fstream
#include <vector> // std::vector
#include <string> // std::string
#include <boost/thread/mutex.hpp> // boost::mutex
#include <boost/noncopyable.hpp> // boost::noncopyable

#include "singleton.hpp" // Singleton

namespace avivilloz
{

class Storage
{
public:
    Storage(std::string pathToStorage);
    void ReadAll(std::vector<std::string> &urls);
    void Append(std::string url);

private:
    std::fstream m_file;
};

class UrlShortener : private boost::noncopyable
{
public:
    std::string GetShortUrl(std::string url);
    std::string GetUrl(std::string shortUrl);

private:
    static const std::string s_pathToStorage;
    static const std::string s_rawUrl;
    static const std::string s_charsMap;
    static const std::size_t s_base;

    Storage m_storage; 
    std::vector<std::string> m_urls;
    std::size_t m_counter;
    boost::mutex m_mutex;

    friend class Singleton<UrlShortener>;
    UrlShortener();

    static std::string GetPathToStorage();
    static std::string GetRawUrl();

    std::size_t GetId(std::string urlOffset);
};

}

#endif // URL_SHORTENER_HPP
