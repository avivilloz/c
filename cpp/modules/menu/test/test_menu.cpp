/*****************************************************************************
 * title: test menu
 * description: testing menu interface
 * author: aviv illoz
*****************************************************************************/

#include <iostream>

#include "menu.hpp"
#include "utils.hpp" // CLEAR

using namespace wallet;

class Hey
{
public:
    void operator()()
    {
        std::cout << CLEAR;
        std::cout << "heeeeeey" << std::endl;
        sleep(2);
    }
};

class Wow
{
public:
    void operator()()
    {
        std::cout << CLEAR;
        std::cout << "wooooow" << std::endl;
        sleep(2);
    }
};

class Startup
{
public:
    void operator()()
    {
        std::cout << "------------" << std::endl;
        std::cout << std::endl;
        std::cout << "budget: 100$" << std::endl;
        std::cout << std::endl;
        std::cout << "------------" << std::endl;
    }
};

int main()
{
    Menu<Startup> menu = Startup();

    boost::shared_ptr<Option> hey(new Action<Hey>(Hey()));
    menu.AddOption(std::string("hey"), hey);

    boost::shared_ptr<Option> wow(new Action<Wow>(Wow()));
    menu.AddOption(std::string("wow"), wow);

    menu();

    return 0;
}
