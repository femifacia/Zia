/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** Http
*/

#ifndef HTTP_HPP_
#define HTTP_HPP_

#include <iostream>
#include "../IModule.hpp"
#include "../../src/Service/Service.hpp"
#include <mutex>
#include <memory>
#include <thread>
#include <vector>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/system/error_code.hpp>
#include "../../src/Client/Client.hpp"

namespace Module {
    class Http : public IModule{
    public:
        /**
         * @brief Close all the connection after they get responses
         * 
         */
        void closeAllConnection(void);

        /**
         * @brief Send a message to another module
         * 
         * @param str 
         */
        void print(std::string str);

        /**
         * @brief Handle each new client
         * 
         * @param client 
         */
        void manageClient(std::shared_ptr<Client> client);

        /**
         * @brief Add Client to the vector
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
         * @brief Construct a new Http object
         * 
         */
        Http();
        
        /**
         * @brief Destroy the Http object
         * 
         */
        ~Http();

        /**
         * @brief the way to call this module when a request is catched
         * 
         * @param trigger 
         * @param request 
         * @param response 
         * @param serviceRoot 
         */
        void launch(std::string trigger, HttpRequest &request, HttpRequest &response, std::string serviceRoot);

        /**
         * @brief Get the Name object
         * 
         * @return std::string 
         */
        std::string getName(void);

        /**
         * @brief Get the Type object
         * 
         * @return int 
         */
        int getType(void);

        /**
         * @brief init the module if necessary
         * 
         */
        int init(std::string);

        /**
         * @brief launch the loop of the module if necessary
         * 
         */
        void run(void);

        /**
         * @brief close the module if necessary
         * 
         */
        void close(void);

        /**
         * @brief Set the Service object
         * 
         * @param service 
         */
        void setService(void *service);

        /**
         * @brief Create a new Http object with factory method
         * 
         * @return boost::shared_ptr<Http> 
         */
        static boost::shared_ptr<Http> create();

    protected:
        /**
         * @brief Launch the module behavior
         * 
         * @param trigger 
         * @param request 
         * @param response 
         * @param serviceRoot 
         */
        void behavior(std::string trigger, HttpRequest &request, HttpRequest &response, std::string serviceRoot);
    
    private:
        int _type;
        std::string _name;
        Service *_service;
        boost::asio::io_context _ioContext;
        boost::asio::ip::tcp::endpoint _endpoint;
        boost::asio::ip::tcp::acceptor _acceptor;
        std::thread _acceptThread;
        std::mutex _acceptMutex;
        std::vector<boost::shared_ptr<Module::IModule>> _moduleArray;
        std::vector<std::shared_ptr<Client>> _clientArray;
    };
}

#endif /* !HTTP_HPP_ */
