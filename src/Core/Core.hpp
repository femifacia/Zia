/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include "../Shell/Shell.hpp"
#include "../Server/Server.hpp"
#include <memory>
#include <iostream>
#include <string>
#include "./ConfigHandler/ConfigHandler.hpp"
#include <exception>

class Core {
    public:

    /**
     * @brief reload conf.ini file
     * 
     */

    void reload(void);

    /**
     * @brief stop the server
     * 
     */

    void stopServer(void);

    /**
     * @brief print a string
     * 
     * @param string 
     */

    void print(std::string string);

    /**
     * @brief run the shell and the server
     * 
     */

    void run(void);

    /**
     * @brief Init the Core
     * 
     */

    void init(void);

    /**
     * @brief Construct a new Core object
     * 
     */
        Core();
    /**
     * @brief Destroy the Core object
     * 
     */
        ~Core();

    /**
     * @brief list each module of each service
     * 
     */

        void listAllService(void);

        /**
         * @brief load a module on a service
         * 
         * @param module 
         * @param service 
         */

        void loadModuleOnService(std::string module, std::string service);

        /**
         * @brief load a module to each service
         * 
         * @param module 
         */

        void loadModuleAllService(std::string module);


    /**
     * @brief unload a module on a service
     * 
     * @param module 
     * @param service 
     */

        void unloadModuleOnService(std::string module, std::string service);

        /**
         * @brief unload a module for each service
         * 
         * @param module 
         */

        void unloadModuleAllService(std::string module);

        /**
         * @brief print log
         * 
         */

        void printLog(void);

        /**
         * @brief Set the Conf Path object
         * 
         * @param path 
         */

        void setConfPath(std::string path);

        /**
         * @brief print the conf.ini path
         * 
         */

        void printConfPath(void);

    protected:
    private:
        std::shared_ptr<Server> _server;
        std::shared_ptr<Shell> _shell;
        std::string _coreName;
        ConfigHandler _configHandler;
};

#endif /* !CORE_HPP_ */
