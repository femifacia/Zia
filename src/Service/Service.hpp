/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** Service
*/

#ifndef SERVICE_HPP_
#define SERVICE_HPP_

#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include "boost/asio.hpp"
#include <memory>
#include "../Client/Client.hpp"
#include <thread>
#include <mutex> 
#include <vector>
#include "../HttpRequest/HttpRequest.hpp"
#include "../../Modules/IModule.hpp"
#include "../Core/DllHandler/DllHandler.hpp"
#include <unordered_map>
#include "../../Modules/Logger/Logger.hpp"


class Service {
    public:

    /**
     * @brief Init and load the module pin charge to the management of the connexion
     * 
     */

    void initNetworkManagement(void);

    /**
     * @brief manage a client
     * 
     * @param client 
     */

    void manageClient(std::shared_ptr<Client> client);

    /**
     * @brief add Client to the vector
     * 
     * @param connection 
     */

    void addClient(TcpConnection::boostPtr connection);

    /**
     * @brief the handler called when a client is accepted
     * 
     * @param newConnection 
     * @param error 
     */
    
    void handleAccept(TcpConnection::boostPtr newConnection, const boost::system::error_code& error);

    /**
     * @brief accept clients
     * 
     */

    void acceptClient(void);

        /**
         * @brief Create object
         * 
         * @param port
         * @param name
         * @param root
         */
        Service(const int port, const std::string name, const std::string networkModuleName, const std::string loggerModuleName, const std::string root);

        /**
         * @brief Destroy object
         * 
         */
        ~Service();

        /**
         * @brief Set the port of the object
         * 
         * @param port 
         * @return ** void 
         */
        void setPort(const int port);

        /**
         * @brief Set the name of the object
         * 
         * @param name 
         * @return ** void 
         */
        void setName(const std::string name);

        /**
         * @brief Set the path of the object
         * 
         * @param root 
         * @return ** void 
         */
        void setPath(const std::string root);

        /**
         * @brief Get the port of the object
         * 
         * @return ** int 
         */
        int getPort(void) const;

        /**
         * @brief Get the name of the object
         * 
         * @return ** std::string 
         */
        std::string getName(void) const;

        /**
         * @brief Get the Module Network object
         * 
         * @return ** std::string 
         */
        std::string getModuleNetwork(void) const;


        /**
         * @brief Get the Module Logger object
         * 
         * @return ** std::string 
         */
        std::string getModuleLogger(void) const;

        /**
         * @brief Get the path of the object
         * 
         * @return ** std::string 
         */
        std::string getPath(void) const;


        /**
         * @brief Get the Mutex object
         * 
         * @return ** std::mutex* 
         */
        std::shared_ptr<std::mutex> getMutex(void) const;

        /**
         * @brief Set the Mutex object
         * 
         * @param m 
         * @return ** void 
         */
        void setMutex(std::shared_ptr<std::mutex>);

        /**
         * @brief Set the Is Running object
         * 
         * @param a 
         * @return ** void 
         */
        void setIsRunning(bool);

        /**
         * @brief Return running state of the object
         * 
         * @return true 
         * @return false 
         */
        bool isRunning(void) const;

        /**
         * @brief Run object
         * 
         * @return ** void 
         */
        void run(void);

        /**
         * @brief Print object information
         * 
         * @return ** void 
         */
        void print(std::string);

        /**
         * @brief stop the service
         * 
         */

        void stop(void);

        /**
         * @brief close all the connection after they get responses
         * 
         */

        void closeAllConnection(void);

        /**
         * @brief 
         * 
         * @param moduleDirectory 
         * @param moduleName 
         */

        void addModule(std::string moduleDirectory, std::string moduleName);

        /**
         * @brief Get the Network Status object
         * 
         * @return int 
         */

        int getNetworkStatus(void);

        /**
         * @brief Set the Network Status object
         * 
         * @param status 
         */

        void setNetworkStatus(int status);

        /**
         * @brief Get the Module Array object
         * 
         * @return std::vector<boost::shared_ptr<Module::IModule>> 
         */

        std::vector<boost::shared_ptr<Module::IModule>> getModuleArray(void);

        /**
         * @brief Get the Root object
         * 
         * @return std::string 
         */

        std::string getRoot(void);

        /**
         * @brief 
         * 
         */

        void listModules(void);

        /**
         * @brief Set the Dll Handler object
         * 
         */

        void setDllHandler(std::shared_ptr<DllHandler>);


        /**
         * @brief init the logger
         * 
         * @return ** void 
         */
        void initLogger(void);


        /**
         * @brief Get the Logger object
         * 
         * @return ** Logger* 
         */
        void writeLog(std::string mess);
    
        /**
         * @brief remove a module
         * 
         * @param name 
         */

        void removeModule(std::string name);

    protected:
    private:


        /**
         * @brief Close object
         * 
         * @return ** void 
         */

        void close(void);
        int _port;
        std::string _name;
        std::string _root;
        std::string _networkModuleName;
        std::string _loggerModuleName;
        std::shared_ptr< std::mutex> _mutex;
        bool _isRunning;
        boost::asio::io_context _ioContext;
        boost::asio::ip::tcp::endpoint _endpoint;
        boost::asio::ip::tcp::acceptor _acceptor;
        std::thread _acceptThread;
        std::mutex _acceptMutex;
        std::vector<std::shared_ptr<Client>> _clientArray;
        //std::shared_ptr<boost::asio::ip::tcp::acceptor> _acceptor;

        std::vector<std::string> _modulePathArray;

        std::vector<boost::shared_ptr<Module::IModule>> _moduleArray;
        std::unordered_map<std::string, boost::shared_ptr<Module::IModule>> _moduleMap;
        std::shared_ptr<DllHandler> _dlhandler;

        boost::shared_ptr<Module::IModule> _networkModule;
        int _networkStatus;

        boost::shared_ptr<Module::IModule> _loggerModule;
};

#endif /* !SERVICE_HPP_ */
