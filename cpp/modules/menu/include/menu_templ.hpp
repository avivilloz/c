/*****************************************************************************
 * title: menu templates
 * description: menu interface templates
 * author: aviv illoz
*****************************************************************************/

#include "menu.hpp" // api
#include "utils.hpp" // CLEAR

namespace wallet
{

template<class T>
Menu<T>::Menu(T startup)
    : m_startup(startup), m_options()
{}

template<class T>
void Menu<T>::AddOption(std::string key, boost::shared_ptr<Option> option)
{
    m_options[key] = option;
}

template<class T>
void Menu<T>::operator()()
{
    std::map<std::string, boost::shared_ptr<Option> >::iterator it;
    std::string exit("exit");
    std::string input;
    
    do
    {
        std::cout << CLEAR;

        m_startup();

        for (it = m_options.begin(); it != m_options.end(); it++)
        {
            std::cout << "-" << it->first << "  ";
        }
        std::cout << "-" << exit << std::endl;

        std::cout << "$ ";
        std::cin >> input;

        it = m_options.find(input);
        if (it != m_options.end())
        {
            (*it->second)(); // call functor
        }

    } while (input != exit);

    std::cout << CLEAR;
}

template<class T>
Action<T>::Action(T func)
    : m_func(func)
{}

template<class T>
void Action<T>::operator()()
{
    m_func();
}

}
