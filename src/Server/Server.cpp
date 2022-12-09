/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** Server
*/

#include "Server.hpp"
#include "../Core/Core.hpp"
std::shared_ptr<DllHandler> createHandler(void);

void Server::printLog(void)
{
}

std::shared_ptr<Service> Server::getService(std::string name)
{
    for (std::shared_ptr<Service> service : _serviceArray) {
        if (service->getName() == name)
            return (service);
    }
    return (nullptr);
}

void Server::loadModuleAllService(std::string mod)
{
    for (std::shared_ptr<Service> service : _serviceArray)
        service->addModule(_pathModuleDirectory, mod);
}

void Server::unloadModuleAllService(std::string mod)
{
    for (std::shared_ptr<Service> service : _serviceArray)
        service->removeModule(mod);
}

void Server::unloadModuleOnService(std::string module, std::string service)
{
    std::shared_ptr<Service> ptr = getService(service);

    if (!ptr) {
        print("/unloadModule ERROR");
        print("No service with the name " + service);
        return;
    }
    ptr->removeModule(module);
}

void Server::loadModuleOnService(std::string module, std::string service)
{
    std::shared_ptr<Service> ptr = getService(service);

    if (!ptr) {
        print("/loadModule ERROR");
        print("No service with the name " + service);
        return;
    }
    ptr->addModule(_pathModuleDirectory, module);
}

void Server::listAllService(void)
{
    for (std::shared_ptr<Service> service : _serviceArray)
        service->listModules();
}

void Server::addAllServices(std::vector<std::shared_ptr<Service>> serviceArray)
{
    //_serviceArray = serviceArray;
    int a = _serviceArray.size();
    for (std::shared_ptr<Service> service : serviceArray)
    {
        service->setDllHandler(createHandler());
        addService(service);
    }
}

void Server::closeAllServices(void)
{
    int size = _serviceArray.size();

    //std::cout << size <<std::endl;
    for (int i = 0; i < size; i++)
    {
        _serviceArray[i]->stop();
        if (_serviceThread[i].joinable())
        {
            _serviceThread[i].join();
        }
    }
}

void Server::reload(std::vector<std::shared_ptr<Service>> services, std::string path, std::vector<std::string> modules)
{
    closeAllServices();
    _serviceMutex.clear();
    _serviceThread.clear();
    _serviceArray.clear();
    std::this_thread::sleep_for(std::chrono::microseconds(10));
    addAllServices(services);
    addAllModules(path, modules);
}

void Server::addService(std::shared_ptr<Service> service)
{
    std::shared_ptr<std::mutex> mmutex(new std::mutex);

    _serviceArray.push_back(service);
    service->setDllHandler(createHandler());
    service->setMutex(mmutex);
    _serviceMutex.push_back(mmutex);
    _service = service;
    _serviceThread.push_back(std::thread([this]()
                                         { _service->run(); }));
    std::this_thread::sleep_for(std::chrono::microseconds(150));
}

void Server::stop(void)
{
    _serverMutex.lock();
    if (!_isRunning)
    {
        _serverMutex.unlock();
        return;
    }
    _isRunning = 0;
    closeAllServices();
    print("I am closing ...");
    _serverMutex.unlock();

    for (std::string e: _moduleArray)
        print (e);
}

void Server::setCore(void *core)
{
    _core = core;
}

void Server::print(std::string message)
{
    std::cout << "[" << _serverName << "]: " << message << std::endl;
}

Server::Server()
{
    _serverName = "Server";
    _core = NULL;
    _isRunning = 1;
    _pathModuleDirectory = "";
}

Server::~Server()
{
}

void Server::addAllModules(std::string path, std::vector<std::string> moduleArray)
{
    int a = _serviceArray.size();

    _pathModuleDirectory = path;
    for (std::shared_ptr<Service> service : _serviceArray)
    {
        for (std::string mod: moduleArray)
            service->addModule(path, mod);
        service->initLogger();
        service->initNetworkManagement();
    }
}

void Server::addAllModules(std::vector<std::shared_ptr<Service>> services, std::string path, std::vector<std::string> moduleArray)
{
    _pathModuleDirectory = path;
    for (std::shared_ptr<Service> service : services)
    {
        for (std::string mod: _moduleArray)
            service->addModule(path, mod);
    }
}