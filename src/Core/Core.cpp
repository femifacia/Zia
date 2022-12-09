/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** Core
*/

#include "Core.hpp"

void Core::printLog(void)
{
    std::ifstream file("../log.txt");
    bool check = 0;
    std::string line;

    if (!file.is_open()) {
        print("ERROR");
        print("No log file found");
        return;
    }
    while (std::getline(file, line)) {
        check = 1;
        std::cout << line << std::endl;
    }
    if (!check)
        std::cout << "No log available" << std::endl;
}

void Core::printConfPath(void)
{
    _configHandler.printFilePath();
}

void Core::setConfPath(std::string path)
{
    _configHandler.setPathFile(path);
}

void Core::unloadModuleAllService(std::string mod)
{
    _server->unloadModuleAllService(mod);
}

void Core::loadModuleAllService(std::string mod)
{
    _server->loadModuleAllService(mod);
}

void Core::unloadModuleOnService(std::string module, std::string service)
{
    _server->unloadModuleOnService(module, service);
}

void Core::loadModuleOnService(std::string module, std::string service)
{
    _server->loadModuleOnService(module, service);
}

void Core::listAllService(void)
{
    _server->listAllService();
}

void Core::stopServer(void)
{
    _server->stop();
}

void Core::print(std::string string)
{
    std::cout << "[" << _coreName << "]: " << string << std::endl;
}

void Core::run(void)
{
    _shell->run();
}

void Core::reload(void)
{
    _configHandler.update();
    //_configHandler.getSe
    _server->reload(_configHandler.getServices(), _configHandler.getModulePath(), _configHandler.getModules());
}

void Core::init(void)
{
    _shell->setCore((void *)this);
    _server->setCore((void *)this);
    _configHandler.update();
    //_configHandler.getSe
 //   _server->addAllModules(_configHandler.getServices(), _configHandler.getModulePath(), _configHandler.getModules());
    _server->addAllServices(_configHandler.getServices());
    _server->addAllModules(_configHandler.getModulePath(), _configHandler.getModules());

}

Core::Core(): _server(new Server()), _shell(new Shell())
{
    _coreName = "ZIA";
    print("... initializing components...");
}

Core::~Core()
{
}
