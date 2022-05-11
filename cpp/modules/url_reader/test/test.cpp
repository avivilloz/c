/*****************************************************************************
 * title: url reader test
 * author: aviv illoz
 * description: testing url reader
*****************************************************************************/

#include <string> // std::string
#include <fstream> // std::ifstream
#include <iostream> // std::cerr, std::endl
#include <string> // std::string, std::getline
#include <stdlib.h> // atoi
#include <boost/thread.hpp> // boost::thread_group
#include <boost/thread/mutex.hpp> // boost::mutex, boost::mutex::scoped_lock

#include "url_reader.hpp" // api
#include "url_shortener.hpp" // UrlShortener
#include "singleton.hpp" // Singleton

using namespace avivilloz;

static boost::mutex g_mutex;
static std::ifstream g_urlsSrcFile;
static std::string g_urlsDestDirPath;

void AddUrlToRead()
{
    UrlReader *urlReader = Singleton<UrlReader>::GetInstance();
    UrlShortener *urlShortener = Singleton<UrlShortener>::GetInstance(); 

    std::string url;

    boost::mutex::scoped_lock lock(g_mutex);

    if (std::getline(g_urlsSrcFile, url))
    {
        urlReader->ReadUrl(url, g_urlsDestDirPath + urlShortener->GetShortUrl(url));
    }
    else
    {
        std::cerr << "no more urls to read" << std::endl;
    }
}

int main(int argc, char *argv[])
{
    std::size_t numOfThreads = atoi(argv[argc - 1]);

    g_urlsDestDirPath = argv[argc - 2];

    std::string urlsSrcFilePath(argv[argc - 3]);
    g_urlsSrcFile.open(urlsSrcFilePath.c_str());

    boost::thread_group tgroup;

    for (std::size_t i = 0; i < numOfThreads; i++)
    {
        tgroup.create_thread(&AddUrlToRead);
    }

    tgroup.join_all();

    return 0;
}
