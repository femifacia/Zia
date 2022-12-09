/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** Services
*/

#include "Service.hpp"

void Service::initNetworkManagement(void)
{
    _mutex->lock();
    boost::shared_ptr<Module::IModule> networkModule = _moduleMap[_networkModuleName];
    _networkStatus = 2;

    if (!networkModule) {
        print("the module " + _networkModuleName + " choosen for Network Management hasn't been loaded");
        _mutex->unlock();
        return;
    }
    if (networkModule->getType() != 1) {

        std::cout << "Type is " << networkModule->getType() << " " << networkModule->getName();
        print("the module " + _networkModuleName + " choosen for Network Management is not a module for connection");
        _mutex->unlock();
        return;
    }
    _networkModule = networkModule;
    _networkModule->setService(this);
    if (!_networkModule->init("")) {
        print("Fail ... I am not running");
        _mutex->unlock();
        return;
    }
    print("I am running on port " + std::to_string(_port));
    _networkStatus = 1;
    _mutex->unlock();
}

void Service::initLogger(void)
{
    _mutex->lock();
     boost::shared_ptr<Module::IModule> loggerModule = _moduleMap[_loggerModuleName];

     if (!loggerModule) {
        print("the module " + _loggerModuleName + " choosen for Logger Management hasn't been loaded");
        _mutex->unlock();
        return;
    }
    if (loggerModule->getType() != 3) {
        print("the module " + _loggerModuleName + " choosen for Logger Management is not a module for logger");
        _mutex->unlock();
        return;
    }
    _loggerModule = loggerModule;
    _loggerModule->setService(this);
    print("The Logger module used is " + _loggerModuleName);
    _mutex->unlock();
}

void Service::writeLog(std::string mess)
{
    _mutex->lock();
    if (!_loggerModule) {
        _mutex->unlock();
        return;
    }
    Module::IModule *ptr = _loggerModule.get();
    Module::Logger *logger = static_cast<Module::Logger*>(ptr);
    logger->write(mess);
    _mutex->unlock();
}

void Service::setDllHandler(std::shared_ptr<DllHandler> handler)
{
    _dlhandler = handler;
}

void Service::listModules(void)
{
    print("Hi");
    if (_networkStatus != 1) {
        print("I am not running cause my Network Module isn't initialized...");
    } else {
        print("I am Running on port " + std::to_string(_port));
        print("My Network Module is " + _networkModuleName);
    }
    print("my modules");
    for (boost::shared_ptr<Module::IModule> module : _moduleArray)
        print(module->getName());
    std::cout << std::endl;
}

void Service::addClient(TcpConnection::boostPtr connection)
{
    std::shared_ptr<Client> client(new Client(connection));

    _clientArray.push_back(client);
}

Service::Service(const int port, const std::string name, const std::string networkModuleName, const std::string loggerModuleName, const std::string root): _endpoint(boost::asio::ip::tcp::v4(), port), _acceptor(_ioContext)
{
    _port = port;
    _name = name;
    _networkModuleName = networkModuleName;
    _loggerModuleName = loggerModuleName;
    _root = root;
    _isRunning = 1;
    _networkModule = nullptr;
    _networkStatus = 0;
    _dlhandler = nullptr;
}

Service::~Service()
{
}

void Service::setPort(const int port)
{
    _port = port;
}

void Service::setName(const std::string name)
{
    _name = name;
}

void Service::setPath(const std::string root)
{
    _root = root;
}

int Service::getPort(void) const
{
    return (_port);
}

std::string Service::getName(void) const
{
    return (_name);
}

std::string Service::getModuleNetwork(void) const
{
    return (_networkModuleName);
}

std::string Service::getModuleLogger(void) const
{
    return (_loggerModuleName);
}

std::string Service::getPath(void) const
{
    return (_root);
}

std::shared_ptr<std::mutex> Service::getMutex(void) const
{
    return (_mutex);
}

void Service::setMutex(std::shared_ptr<std::mutex> mutex)
{
    _mutex = mutex;
}

void Service::setIsRunning(bool isRunning)
{
    _mutex->lock();
    _isRunning = isRunning;
    _mutex->unlock();
}

int Service::getNetworkStatus(void)
{
    _mutex->lock();
    std::this_thread::sleep_for(std::chrono::microseconds(10));
    _mutex->unlock();
    return (_networkStatus);
}

void Service::setNetworkStatus(int status)
{
    _mutex->lock();
    _networkStatus = status;
    _mutex->unlock();
}

bool Service::isRunning(void) const
{
    _mutex->lock();
    std::this_thread::sleep_for(std::chrono::microseconds(10));
    _mutex->unlock();
    return (_isRunning);
}

void Service::stop(void)
{
    print("Stop received");
    setIsRunning(0);
}

void Service::handleAccept(TcpConnection::boostPtr newConnection, const boost::system::error_code& error)
{
    _acceptMutex.lock();
    if (!error) {
        print("New Client Accepted");
        addClient(newConnection);
    } else
        print("New Client Rejected");
    _acceptMutex.unlock();
    acceptClient();
}

void Service::acceptClient(void)
{
    TcpConnection::boostPtr newConnection = TcpConnection::createBoostPtr(_ioContext);

    _acceptor.async_accept(newConnection->getSocket(), boost::bind(&Service::handleAccept, this, newConnection, boost::placeholders::_1));
}

void Service::manageClient(std::shared_ptr<Client> client)
{
    boost::system::error_code ec;
    int bytess = client->bytesAvailables();
    std::vector<char> buffer(bytess);
    std::string message;
    int size = 0;

    if (bytess == 0)
        return;
    while (bytess) {
        client->getSocket().read_some(boost::asio::buffer(buffer.data(), buffer.size()), ec);
        for (char c : buffer)
            message.append(1, c);
        size = buffer.size();
        for (int i = 0; i < size; i++)
            buffer[i] = '\0';
        bytess = client->bytesAvailables();
    }

    HttpRequest request(message), response;

    for (boost::shared_ptr<Module::IModule> ptr: _moduleArray)
        ptr->launch("", request, response, _root);
    client->sendMessage(response.generate());
    client->close();
}

void Service::closeAllConnection(void)
{
    int i = 0;
    int clientSize = 0;

    clientSize = _clientArray.size();
    while (i < clientSize) {
        for (i = 0; i < clientSize; i++) {
            if (!_clientArray[i]->isConnected()) {
                _clientArray[i]->close();
                _clientArray.erase(_clientArray.begin() + i);
                break;
            }
        }
        clientSize = _clientArray.size();
    }
}

void Service::run(void)
{
    try {
        while (!getNetworkStatus());
        if (getNetworkStatus() == 1) {
            _networkModule->run();
        }
        while(isRunning())
        {
            if (_networkModule)
                _networkModule->run();
        }
        close();
    } catch (std::exception& ex) {
        print("Port " + std::to_string(_port) + " is Already used");
        print("Fail ... I am not running");
        while (isRunning());
        close();
    }
}

std::string Service::getRoot(void)
{
    return (_root);
}

void Service::print(std::string str)
{
    std::cout << "[" << _name << "]: " << str << std::endl;
}

void Service::close(void)
{
    if (_networkModule) {
        _networkModule->close();
    }
    print("I'm closing");
}

void Service::removeModule(std::string moduleName)
{
    _mutex->lock();
    boost::shared_ptr<Module::IModule> myModule = _moduleMap[moduleName];
    int pos = 0;

    if (moduleName == _networkModuleName)
    {
        print("/unloadModule ERROR");
        print("can't unload module " + moduleName + " because it is the network mdoule");
        _mutex->unlock();
        return;
    }
    if (!myModule) {
        print("/unloadModule ERROR");
        print("can't unload module " + moduleName + " because it is not loaded");
        _mutex->unlock();
        return;
    }
    pos = -1;
    int size = _moduleArray.size();

    for (int i = 0; i < size; i++) {
        if (_moduleArray[i] == myModule) {
            pos = i;
            break;
        }
    }
    if (pos < 0) {
        print("/unloadModule ERROR");
        print("can't unload module " + moduleName + " because it is not loaded");
        _mutex->unlock();
        return;
    }
    _moduleArray.erase(_moduleArray.begin() + pos);
    _moduleMap[moduleName] = nullptr;
    if (moduleName == _loggerModuleName)
        _loggerModule = nullptr;
    print(moduleName + " has been unloaded");
    _mutex->unlock();
}

void Service::addModule(std::string moduleDirectory, std::string moduleName)
{
    std::string modulePath = "";
    std::string name = moduleName;

    _mutex->lock();
    #ifdef __linux__
        moduleName = "lib" + moduleName + ".so";
    #elif _WIN32
        moduleName += ".dll";
        moduleDirectory = "bin/";
    #elif _WIN84
        moduleName += ".dll";
    #endif

    modulePath = moduleDirectory + moduleName;

    if (_moduleMap[name]) {
        print("Error in load Module process");
        print("The Module " + name + " already added");
        _mutex->unlock();
        return;
    }

    _modulePathArray.push_back(modulePath);
    boost::shared_ptr<Module::IModule> myModule = _dlhandler->openLib(modulePath);
    if (myModule) {
        print("Module " + modulePath + " has been loaded");
        _moduleArray.push_back(myModule);
        _moduleMap[name] = myModule;
        myModule->setService(this);
    }
    else {
        print("Module " + modulePath + " hasn't been loaded. Check your path in the zia.ini");
    }
    _mutex->unlock();
}

std::vector<boost::shared_ptr<Module::IModule>> Service::getModuleArray(void)
{
    return (_moduleArray);
}