/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** DllHandler
*/

#ifndef DLLHANDLER_HPP_
#define DLLHANDLER_HPP_

#include <iostream>
#include <boost/dll/import.hpp>
#include "../../../Modules/IModule.hpp"
#include <boost/function.hpp>
#include <unordered_map>

typedef boost::shared_ptr<Module::IModule>(module_create_t)();

class DllHandler {
    public:
        DllHandler();
        ~DllHandler();
        boost::shared_ptr<Module::IModule> openLib(std::string path);
    protected:
    private:
        boost::function<module_create_t> _creator;
        std::unordered_map<std::string, boost::function<module_create_t>> _creatorMap;
};

#endif /* !DLLHANDLER_HPP_ */
