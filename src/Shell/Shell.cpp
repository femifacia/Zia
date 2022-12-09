/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** Shell
*/

#include "Shell.hpp"
#include "../Core/Core.hpp"
#include <stdio.h>

void Shell::launchQuit(void)
{
    Core *core = (Core *)_core;

    core->stopServer();        
    setRunning(0);
}

std::vector<std::string> Shell::spliter(std::string str, std::string delim)
{
    std::size_t pos = 0;
    std::string token = "";
    std::vector<std::string> vec = {};

    if (str == "") {
        vec.push_back("");
        return (vec);
    }
    while ((pos = str.find(delim)) != std::string::npos)
    {
        token = str.substr(0, pos);
        if (token != "")
            vec.push_back(token);
        str.erase(0, pos + delim.length());
    }
    if (str != "")
        vec.push_back(str);
    return (vec);
}


void stopShell(const boost::system::error_code &error, int sig)
{
    Shell *shell = saveShell(NULL);

    if (sig == SIGINT || sig == SIGTERM) {
        std::cout << std::endl;
        shell->launchQuit();
        //shell->setRunning(0);
        //shell->stop();
    }
}

Shell *saveShell(Shell *data)
{
    static Shell *shell = NULL;

    if (data)
        shell = data;
    return (shell);
} 

bool Shell::isRunning(void)
{
    //write(1, "b", 1);
    _signalMutex.lock();
    std::this_thread::sleep_for(std::chrono::microseconds(10));
    _signalMutex.unlock();
    return (_isRunning);
}

void Shell::setRunning(bool isRunning)
{
    //write(1, "a", 1);
    _signalMutex.lock();
    _isRunning = isRunning;
    _signalMutex.unlock();
}

void Shell::stop(void)
{
    _ioService.stop();
    if (_shellThread.joinable())
        _shellThread.join();
    print("Is stopping");
}

void Shell::launchReload(void)
{
    Core *core = (Core *)_core;

    print("Reloading ...");
    core->reload();
}

void Shell::printHelp(std::vector<std::string> arg, int argSize)
{
    std::vector<std::string> helpTextVec;

    helpTextVec.push_back("Shell Command");
    helpTextVec.push_back("");
    helpTextVec.push_back("/help");
    helpTextVec.push_back("Print This help");
    helpTextVec.push_back("/quit");
    helpTextVec.push_back("quit the shell");
    helpTextVec.push_back("");
    helpTextVec.push_back("/exit");
    helpTextVec.push_back("");
    helpTextVec.push_back("quit the shell");
    helpTextVec.push_back("/list");
    helpTextVec.push_back("list all informations about each service actually loaded");
    helpTextVec.push_back("");
    helpTextVec.push_back("/loadModule ModuleName");
    helpTextVec.push_back("load the Module to each service actually loaded");
    helpTextVec.push_back("");
    helpTextVec.push_back("/loadModule ModuleName ServiceName");
    helpTextVec.push_back("load the Module to the service selected");
    helpTextVec.push_back("");
    helpTextVec.push_back("/unloadModule ModuleName");
    helpTextVec.push_back("load the Module to each service actually loaded");
    helpTextVec.push_back("");
    helpTextVec.push_back("/unloadModule ModuleName ServiceName");
    helpTextVec.push_back("load the Module to the service selected");
    helpTextVec.push_back("");
    helpTextVec.push_back("/log");
    helpTextVec.push_back("print All the logs availables");
    helpTextVec.push_back("");
    helpTextVec.push_back("/setConfPath Path");
    helpTextVec.push_back("set the conf file path to the one you passed in argument");
    helpTextVec.push_back("");
    helpTextVec.push_back("/printConfPath");
    helpTextVec.push_back("print the path to the conf file used by the zia");
    helpTextVec.push_back("");

    print("This is Help section");
    for (std::string line : helpTextVec)
        std::cout << line << std::endl;
}

void Shell::loadModule(std::vector<std::string> arg, int argSize)
{
    Core *core = NULL;

    if (argSize < 2 || argSize > 3) {
        print("Error");
        print("/loadModule module_name");
        print("/loadModule module_name service");
        return ;
    }
    core = (Core *)_core;
    if (argSize == 3)
        core->loadModuleOnService(arg[1], arg[2]);
    if (argSize == 2)
        core->loadModuleAllService(arg[1]);
}

void Shell::unloadModule(std::vector<std::string> arg, int argSize)
{
    Core *core = NULL;

    if (argSize < 2 || argSize > 3) {
        print("Error");
        print("/loadModule module_name");
        print("/loadModule module_name service");
        return ;
    }
    core = (Core *)_core;
    if (argSize == 3)
        core->unloadModuleOnService(arg[1], arg[2]);
    if (argSize == 2)
        core->unloadModuleAllService(arg[1]);
}

void Shell::printLog(std::vector<std::string> arg, int argSize)
{
    Core *core = NULL;

    if (argSize != 1) {
        print("Error");
        print("/printLog");
        return ;
    }
    core = (Core *)_core;
    core->printLog();
}

void Shell::printConfPath(std::vector<std::string> arg, int argSize)
{
    Core *core = NULL;

    if (argSize != 1) {
        print("Error");
        print("/printConfPath");
        return ;
    }
    core = (Core *)_core;
    core->printConfPath();
}

void Shell::setConfPath(std::vector<std::string> arg, int argSize)
{
    Core *core = NULL;

    if (argSize != 2) {
        print("Error");
        print("/setConfPath path");
        return;
    }
    core = (Core *)_core;
    core->setConfPath(arg[1]);
}

void Shell::launchList(std::vector<std::string> arg, int argSize)
{
    Core *core = NULL;

    if (argSize != 1) {
        print("/list (no args)");
        return;
    }
    core = (Core *)_core;
    core->listAllService();
}

void Shell::manageInput(std::string input)
{
    Core *core = (Core *)_core;
    std::vector<std::string> arg = spliter(input, " ");
    int argSize = arg.size();
    void (Shell::*ptr)(std::vector<std::string>, int);


    if (argSize && (arg[0] == "/quit" || arg[0] == "/exit")) {
        launchQuit();
    }
    if (argSize && (arg[0] == "/reload")) {
        launchReload();
        return;
    }
    ptr = _functionMap[arg[0]];
    if (ptr)
        (this->*ptr)(arg, argSize);
    /*if (input == "/quit" || input == "/exit") {
        core->stopServer();        
        setRunning(0);
    }*/
}

void Shell::run()
{
    Core *core = (Core *)_core;
    std::string input = "";

    print("I am ready for your instructions");
    _shellThread = std::thread([this]{_ioService.run();});
    //_ioService.run();
    //mettre le run dans un contexte
    while (isRunning()) {
        input = getInput();
        manageInput(input);
    }
    stop();
}

void Shell::setCore(void *core)
{
    _core = core;
}

void Shell::print(std::string string)
{
    std::cout << "[" << _shellName << "]: " << string << std::endl;
}

std::string Shell::getInput(void)
{
    std::string input = "";
    static bool isRunning =  1;
    
    //if (isRunning)
        std::cout << ">>";
    if (!std::getline(std::cin, input)) {
        launchQuit();
    }
    return (input);
}

Shell::Shell(): _signal(_ioService, SIGINT, SIGTERM)
{
    _core = NULL;
    _isRunning = 1;
    _shellName = "Shell";
    saveShell(this);
    _signal.async_wait(stopShell);
    _functionMap["/help"] = &Shell::printHelp;
    _functionMap["/loadModule"] = &Shell::loadModule;
    _functionMap["/unloadModule"] = &Shell::unloadModule;
    _functionMap["/list"] = &Shell::launchList;
    _functionMap["/setConfPath"] = &Shell::setConfPath;
    _functionMap["/printConfPath"] = &Shell::printConfPath;
    _functionMap["/log"] = &Shell::printLog;
}

Shell::~Shell()
{
}
