/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** main
*/

#include <boost/asio.hpp>
#include <boost/dll.hpp>
#include <iostream>
#include "../Modules/IModule.hpp"
#include "Core/Core.hpp"
#include "Core/DllHandler/DllHandler.hpp"

std::shared_ptr<DllHandler> createHandler(void)
{
    static std::vector<std::shared_ptr<DllHandler>> vecHandler;
    std::shared_ptr<DllHandler> handler(new DllHandler());

    vecHandler.push_back(handler);
    return (handler);
}

void checkHelp(int argc, char **argv)
{
    if (argc != 2)
        return;
    std::string arg(argv[1]);
    if (arg == "--help" || arg == "-h") {
        std::cout << "zia API" << std::endl;
        std::cout << "A web server" << std::endl;
        std::cout << "--> How to launch <--" << std::endl;
        std::cout << "after compilation step (refer to Readme.md) Go to build file" << std::endl;
        std::cout << "in build file (be careful you have to launch it from the build file)" << std::endl;
        std::cout << "./bin/zia" << std::endl;
        std::cout << std::endl;
        std::cout << "--> To know how to use open the Readme.md" << std::endl;
        std::cout << "--> This is the link of the repository https://github.com/EpitechPromo2024/B-YEP-500-COT-5-1-zia-damia.tobossi.git" << std::endl;
    }
    exit(0);
}

int main(int ac, char **av)
{
    checkHelp(ac, av);
    try {
        Core core;
        core.init();
        core.run();
    } catch(std::exception &exception) {
        std::cerr << exception.what();
        return (84);
    }
    return (0);
}