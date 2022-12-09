/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** SSL
*/

#ifndef SSL_HPP_
#define SSL_HPP_

#include "../IModule.hpp"
#include "../../src/HttpRequest/HttpRequest.hpp"
#include "SslConnexion/SslConnexion.hpp"
#include "../../src/Service/Service.hpp"
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/system/error_code.hpp>
#include <mutex>
#include <memory>
#include <thread>
#include <vector>

namespace Module {
    class Ssl : public IModule
    {
    public:
        /**
         * @brief Construct a new SSL object
         * 
         */
        Ssl();
        
        /**
         * @brief Destroy the SSL object
         * 
         */
        ~Ssl();

        /**
         * @brief The handler when a new client try to connect ot our service
         * 
         * @param connection 
         * @param error 
         */
        void handleAccept(std::shared_ptr<SslConnexion> connection, const boost::system::error_code& error);

        /**
         * @brief Print a message to another module
         * 
         * @param str 
         */
        void print(std::string str);

        /**
         * @brief Add this connection to the array
         * 
         * @param connection 
         */
        void addConnection(std::shared_ptr<SslConnexion> connection);

        /**
         * @brief Launch the module behavior
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
         * @brief Init the module if necessary
         * 
         */
        int init(std::string);

        /**
         * @brief Launch the loop of the module if necessary
         * 
         */
        void run(void);

        /**
         * @brief Close the module if necessary
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
         * @brief Get the Password object
         * 
         * @return std::string 
         */
        std::string getPassword(void) const;

         /**
         * @brief start accept sll client
         * 
         */
        void acceptClient(void);

        /**
         * @brief Manage a connexion
         * 
         * @param connexion 
         */
        void manageClient(std::shared_ptr<SslConnexion> connexion);

        /**
         * @brief Create a new Ssl object with factory method
         * 
         * @return ** boost::shared_ptr<Ssl> 
         */
        static boost::shared_ptr<Ssl> create();

    protected:
        /**
         * @brief Launch the behavior of the SSL Module
         * 
         * @param trigger 
         * @param request 
         * @param response 
         * @param serviceRoot 
         */
        void behavior(std::string trigger, HttpRequest &request, HttpRequest &response, std::string serviceRoot);

    private:
        boost::asio::io_context _ioContext;
        boost::asio::ssl::context _context;
        boost::asio::ip::tcp::acceptor _acceptor;
        int _type;
        std::string _name;
        Service *_service;
        std::thread _acceptThread;
        std::mutex _acceptMutex;
        std::mutex _readMutex;
        std::vector<boost::shared_ptr<IModule>> _moduleArray;
        std::vector<std::shared_ptr<SslConnexion>> _sslConnexionArray;
        std::string _permFile;
        std::string _keyFile;
    };
}

#endif /* !SSL_HPP_ */
