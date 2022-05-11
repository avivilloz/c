/*****************************************************************************
* title: test url shortener
* author: aviv illoz
* description: test url shortener api
******************************************************************************/

#include <string> // std::string
#include <iostream> // std::cout, std::endl

#include "url_shortener.hpp" // api
#include "singleton.hpp"

using namespace avivilloz;

int main()
{
    std::string url1("https://docs.google.com/spreadsheets/d/1UtWOWwrZvDuVv0BvQtTDNyy6vSKb57JH1FCxhGBc49A/edit#gid=510392859");
    std::string url2("https://brainfuel.infinitylabs.co.il/material_frame");
    std::string url3("https://en.cppreference.com/w/cpp/string/basic_string");
    std::string url4("https://stackoverflow.com/questions/35045781/no-matching-function-for-call-to-stdbasic-ofstreamchar-stdchar-traitscha");
    std::string url5("https://stackoverflow.com/questions/34723247/difference-between-stdfstreamx-and-stdiosx-in-c");

    DataRepository *dr = Singleton<DataRepository>::GetInstance();

    /*
    std::string surl1 = dr->GetShortUrl(url1);
    std::string surl2 = dr->GetShortUrl(url2);
    std::string surl3 = dr->GetShortUrl(url3);
    std::string surl4 = dr->GetShortUrl(url4);
    std::string surl5 = dr->GetShortUrl(url5);

    std::cout << surl1 << " is short url for: " << dr->GetUrl(surl1) << std::endl;
    std::cout << surl2 << " is short url for: " << dr->GetUrl(surl2) << std::endl;
    std::cout << surl3 << " is short url for: " << dr->GetUrl(surl3) << std::endl;
    std::cout << surl4 << " is short url for: " << dr->GetUrl(surl4) << std::endl;
    std::cout << surl5 << " is short url for: " << dr->GetUrl(surl5) << std::endl;
    */

    for (std::size_t i = 0; i < 1000000; ++i)
    {
        std::string surl1 = dr->GetShortUrl(url1);
        std::cout << surl1 << " is short url for: " << dr->GetUrl(surl1) << std::endl;
    }

    return 0;
}
