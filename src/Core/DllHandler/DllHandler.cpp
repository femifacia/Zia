/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** DllHandler
*/

#include "DllHandler.hpp"
#include <iostream>

boost::shared_ptr<Module::IModule> DllHandler::openLib(std::string path) 
{
    boost::dll::fs::path lib_path(path);  
    
    try {
        _creator = boost::dll::import_alias<module_create_t>(
            path,
            "createModule",
            boost::dll::load_mode::append_decorations
            );
        
        boost::shared_ptr<Module::IModule> myModule = _creator();
        if (!_creatorMap[myModule->getName()])
            _creatorMap[myModule->getName()] = _creator;
        return myModule;
    } catch (const boost::system::system_error &err) {
        std::cerr << "Cannot load Symbol from " << lib_path << std::endl;
        std::cerr << err.what() << std::endl;
        return nullptr;
    }
    return nullptr;
}

DllHandler::DllHandler()
{
}

DllHandler::~DllHandler()
{
}