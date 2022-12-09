/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include "../Service/Service.hpp"
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

class Server {
    public:

    /**
     * @brief Reload Services
     * 
     * @param Services 
     */

    void reload(std::vector<std::shared_ptr<Service>> Services, std::string path, std::vector<std::string> modules);

    /**
     * @brief add All services loaded from configuration
     * 
     */

    void addAllServices(std::vector<std::shared_ptr<Service>>);

    /**
     * @brief close all actives services
     * 
     */

    void closeAllServices(void);

    /**
     * @brief stop the server
     * 
     */

    void stop();

    /**
     * @brief Construct a new Server object
     * 
     */
        Server();
    /**
     * @brief Destroy the Server object
     * 
     */
        ~Server();

    /**
     * @brief print a message on the standard output
     * 
     * @param message 
     */
        void print(std::string message);

    /**
     * @brief Set the Core object
     * 
     * @param core 
     */

        void setCore(void *core);

        /**
         * @brief add a Service to the array of services
         * 
         * @param service 
         */

        void addService(std::shared_ptr<Service> service);



        /**
         * @brief add a Module to the array of modules
         * 
         * @param module 
         * @return ** void 
         */
        void addModule(std::string module);


        /**
         * @brief add all modules into the array of modules
         * 
         * @param path 
         * @param module 
         * @return ** void 
         */
        void addAllModules(std::string path, std::vector<std::string> module);



        /**
         * @brief add all modules into the array of modules
         * 
         * @param services 
         * @return ** void 
         */
        void addAllModules(std::vector<std::shared_ptr<Service>> services, std::string path, std::vector<std::string> moduleArray);


        /**
         * @brief list each module of each service
         * 
         */
        void listAllService(void);

    /**
     * @brief load  a module to one service
     * 
     * @param module 
     * @param service 
     */

        void loadModuleOnService(std::string module, std::string service);

        /**
         * @brief Get the Service object
         * 
         * @param serviceName 
         * @return std::shared_ptr<Service> 
         */

        std::shared_ptr<Service> getService(std::string serviceName);

        /**
         * @brief load a module to each service
         * 
         * @param module 
         */

        void loadModuleAllService(std::string module);


        /**
         * @brief unload A module on a service
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

         void printLog(void);


    protected:
    private:

    std::vector<std::string> _moduleArray;



    std::vector<std::shared_ptr<Service>> _serviceArray;
    std::string _serverName;
    void *_core;
    std::vector<std::thread> _serviceThread;
    std::vector<std::shared_ptr<std::mutex>> _serviceMutex;
    std::mutex _serverMutex;
    bool _isRunning;
    std::shared_ptr<Service> _service;
    std::string _pathModuleDirectory;
};

#endif /* !SERVER_HPP_ */
