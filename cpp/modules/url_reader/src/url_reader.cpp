/*****************************************************************************
 * title: url reader
 * author: aviv illoz
 * description: defines api for Url Reader
*****************************************************************************/

#include <iostream> // cout, endl
#include <string> // std::string
#include <fstream> // std::ofstream
#include <boost/bind.hpp> // boost::bind
#include <boost/thread/mutex.hpp> // boost::mutex
#include <curl/curl.h> // curl lib
#include <stdio.h> // FILE*
#include <stdlib.h> // atoi

#include "url_reader.hpp" // api
#include "singleton.hpp" // Singleton
#include "runtime_config.hpp" // RuntimeConfig
#include "utils.hpp" // ThrowIfBad

namespace avivilloz
{

const std::size_t UrlReader::s_curlPollTimeout(GetCurlPollTimeout());

std::size_t UrlReader::GetCurlPollTimeout()
{
    RuntimeConfig *config = Singleton<RuntimeConfig>::GetInstance();
    return atoi(config->GetValue(CURL_POLL_TIMEOUT).c_str());
}

UrlReader::CurlGlobal::CurlGlobal()
{
    CURLcode globalStat = curl_global_init(CURL_GLOBAL_ALL);
    ThrowIfBad<std::runtime_error>(0 != globalStat, "curl_global_init() failed");
}

UrlReader::CurlGlobal::~CurlGlobal()
{
    curl_global_cleanup();
}

UrlReader::Userp::Userp(Output_t ot, const std::string &url, void *dest)
    : m_ot(ot), m_url(url), m_dest(dest)
{}

UrlReader::Userp::~Userp()
{
    if (WRITE_IN_FILE == m_ot)
    {
        delete static_cast<char*>(m_dest);
    }
}

UrlReader::UrlReader()
    : m_curlGlobal(), 
      m_multiHandle(curl_multi_init()), 
      m_isRunning(0),
      m_tgroup(),
      m_mutex()
{}

UrlReader::~UrlReader()
{
    m_tgroup.join_all();
    CURLMcode multiStat = curl_multi_cleanup(m_multiHandle);
    ThrowIfBad<std::runtime_error>(CURLM_OK != multiStat, curl_multi_strerror(multiStat));
}

void UrlReader::ReadUrl(const std::string &url, const std::string &destFilePath)
{
    char *destFilePathPtr = new char[destFilePath.size() + 1];
    memcpy(destFilePathPtr, destFilePath.c_str(), destFilePath.size() + 1);

    Userp *userp(new Userp(WRITE_IN_FILE, url, destFilePathPtr));

    AddEasyHandle(url, &UrlReader::OutputToFile, userp);
}

void UrlReader::ReadUrl(const std::string &url, char *buf)
{
    Userp *userp(new Userp(WRITE_IN_BUFFER, url, buf)); 

    AddEasyHandle(url, &UrlReader::OutputToBuffer, userp);
}

void UrlReader::ReadUrl(const std::string &url)
{
    Userp *userp(new Userp(WRITE_IN_TERMINAL, url, NULL));

    AddEasyHandle(url, &UrlReader::OutputToTerminal, userp);
}

void UrlReader::AddEasyHandle(const std::string &url, OutputFunc_t func, Userp *userp)
{
    CURL *easyHandle = curl_easy_init();
    ThrowIfBad<std::runtime_error>(NULL == easyHandle, "curl_easy_init() failed");

    CURLcode easyStat = curl_easy_setopt(easyHandle, CURLOPT_WRITEFUNCTION, func);
    ThrowIfBad<std::runtime_error>(CURLE_OK != easyStat, curl_easy_strerror(easyStat));

    easyStat = curl_easy_setopt(easyHandle, CURLOPT_WRITEDATA, userp);
    ThrowIfBad<std::runtime_error>(CURLE_OK != easyStat, curl_easy_strerror(easyStat));

    easyStat = curl_easy_setopt(easyHandle, CURLOPT_PRIVATE, userp);
    ThrowIfBad<std::runtime_error>(CURLE_OK != easyStat, curl_easy_strerror(easyStat));

    easyStat = curl_easy_setopt(easyHandle, CURLOPT_URL, url.c_str());
    ThrowIfBad<std::runtime_error>(CURLE_OK != easyStat, curl_easy_strerror(easyStat));

    boost::mutex::scoped_lock lock(m_mutex);
    
    CURLMcode multiStat = curl_multi_add_handle(m_multiHandle, easyHandle);
    ThrowIfBad<std::runtime_error>(CURLM_OK != multiStat, curl_multi_strerror(multiStat));
    
    if (0 == m_isRunning)
    {
        m_isRunning = 1;
        m_tgroup.create_thread(boost::bind(&UrlReader::Run, this));
    }
}

void UrlReader::Run()
{
    std::cout << "copying urls data..." << std::endl;

    while (m_isRunning)
    {
        CURLMcode multiStat = curl_multi_poll(m_multiHandle, NULL, 0, s_curlPollTimeout, NULL);
        ThrowIfBad<std::runtime_error>(CURLM_OK != multiStat, curl_multi_strerror(multiStat));

        multiStat = CURLM_CALL_MULTI_PERFORM;

        boost::mutex::scoped_lock lock(m_mutex);

        while (CURLM_CALL_MULTI_PERFORM == multiStat)
        {
            multiStat = curl_multi_perform(m_multiHandle, &m_isRunning);
        }

        ThrowIfBad<std::runtime_error>(CURLM_OK != multiStat, curl_multi_strerror(multiStat));
    }

    std::cout << "finished copying urls data..." << std::endl;

    CheckMultiInfo();
}

void UrlReader::CheckMultiInfo()
{
    CURLMsg *msg = NULL;
    int pending = 0;

    while ((msg = curl_multi_info_read(m_multiHandle, &pending)) && pending)
    {
        if (CURLMSG_DONE == msg->msg) 
        {
            CURL *easyHandle = msg->easy_handle;
            Userp *userp = NULL;

            CURLcode easyStat = curl_easy_getinfo(easyHandle, CURLINFO_PRIVATE, &userp);
            ThrowIfBad<std::runtime_error>(CURLE_OK != easyStat, curl_easy_strerror(easyStat));

            std::cerr << userp->m_url << " done: " << curl_easy_strerror(msg->data.result) << std::endl;

            delete userp; // created in ReadUrl method

            CURLMcode multiStat = curl_multi_remove_handle(m_multiHandle, easyHandle);
            ThrowIfBad<std::runtime_error>(CURLM_OK != multiStat, curl_multi_strerror(multiStat));

            curl_easy_cleanup(easyHandle);
        }
    }
}

std::size_t UrlReader::OutputToFile(char *data, std::size_t size, std::size_t nmemb, void *userp)
{
    char *destFilePath = static_cast<char*>(static_cast<Userp*>(userp)->m_dest);
    std::ofstream destFile(destFilePath, std::ios::app);

    destFile << data;

    return nmemb * size;
}

std::size_t UrlReader::OutputToBuffer(char *data, std::size_t size, std::size_t nmemb, void *userp)
{
    char *buf = static_cast<char*>(static_cast<Userp*>(userp)->m_dest);

    memcpy(buf, data, nmemb * size);

    return nmemb * size;
}

std::size_t UrlReader::OutputToTerminal(char *data, std::size_t size, std::size_t nmemb, void *userp)
{
    std::cout << data << std::endl;

    (void)userp;

    return nmemb * size;
}

}
