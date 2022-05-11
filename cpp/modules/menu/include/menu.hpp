/*****************************************************************************
 * title: menu
 * description: menu interface
 * author: aviv illoz
*****************************************************************************/

#ifndef MENU_HPP
#define MENU_HPP

#include <map> // std:map
#include <string> // std::string

#include "boost/shared_ptr.hpp" // boost::shared_ptr

namespace wallet
{

class Option
{
public:
    virtual ~Option() = 0;
    virtual void operator()() = 0;
};

template<class T>
class Menu : public Option
{
public:
    Menu(T startup);
    void AddOption(std::string key, boost::shared_ptr<Option> option);
    void operator()();

private:
    T m_startup;
    std::map<std::string, boost::shared_ptr<Option> > m_options;
};

template<class T>
class Action : public Option
{
public:
    Action(T func);
    void operator()();

private:
    T m_func;
};

}

#include "menu_templ.hpp"

#endif // WALLET_HPP
