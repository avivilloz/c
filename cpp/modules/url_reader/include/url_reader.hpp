/*****************************************************************************
 * title: url reader
 * author: aviv illoz
 * description: defines api for url reader
*****************************************************************************/

#ifndef URL_READER_HPP
#define URL_READER_HPP

#include <string> // std::string
#include <boost/thread/mutex.hpp> // boost::mutex
#include <boost/noncopyable.hpp> // boost::noncopyable
#include <boost/thread.hpp> // boost::thread_group
#include <curl/curl.h> // curl lib

#include "singleton.hpp" // Singleton

namespace avivilloz
{

class UrlReader : private boost::noncopyable
{
public:
    ~UrlReader();

    // write in file
    void ReadUrl(const std::string &url, const std::string &destFilePath);

    // write in buffer
    void ReadUrl(const std::string &url, char *buf);

    // write in terminal
    void ReadUrl(const std::string &url);

private:
    struct CurlGlobal
    {
        CurlGlobal();
        ~CurlGlobal();
    };

    enum Output_t {WRITE_IN_FILE, WRITE_IN_BUFFER, WRITE_IN_TERMINAL};

    struct Userp
    {
        Userp(Output_t ot, const std::string &url, void *dest);
        ~Userp();

        Output_t m_ot;
        std::string m_url;
        void *m_dest;
    };

    static const std::size_t s_curlPollTimeout;

    CurlGlobal m_curlGlobal;
    CURLM *m_multiHandle;
    int m_isRunning;
    boost::thread_group m_tgroup;
    boost::mutex m_mutex;

    typedef std::size_t (*OutputFunc_t)(char *data, std::size_t size, std::size_t nmemb, void *userp);

    friend class Singleton<UrlReader>;
    UrlReader();

    static std::size_t GetCurlPollTimeout();

    void AddEasyHandle(const std::string &url, OutputFunc_t func, Userp *userp);
    void Run();
    void CheckMultiInfo();

    static std::size_t OutputToFile(char *data, std::size_t size, std::size_t nmemb, void *userp);
    static std::size_t OutputToBuffer(char *data, std::size_t size, std::size_t nmemb, void *userp);
    static std::size_t OutputToTerminal(char *data, std::size_t size, std::size_t nmemb, void *userp);
};

}

#endif // URL_READER_HPP
