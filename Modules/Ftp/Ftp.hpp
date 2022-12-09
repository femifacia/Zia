/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** Ftp
*/

#ifndef FTP_HPP_
#define FTP_HPP_

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

    class Ftp : public IModule{

        public:
        static int _nbrInstance;

        /**
         * @brief Construct a new Ftp object
         * 
         */

            Ftp();

            /**
             * @brief Destroy the Ftp object
             * 
             */
            ~Ftp();


        int getNbrInstances(void);
        boost::shared_ptr<IModule> newPtr(void);


            /**
             * @brief close all the connection after they get responses
             * 
             */

        void closeAllConnection(void);

    /**
     * @brief print a string on the log
     * 
     * @param str 
     */

        void print(std::string str);

        /**
         * @brief clean the ftp string
         * 
         * @param str 
         */

        void cleanFtpRequest(std::string &str);


        /**
         * @brief split a string
         * 
         * @param str 
         * @param delim 
         * @return std::vector<std::string> 
         */
        
        std::vector<std::string> spliter(std::string str, std::string delim);

        /**
         * @brief manage client
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
             * @brief Launch Help Command
             * 
             * @param arg 
             * @param argSize 
             */

            void launchHelp(std::shared_ptr<Client>, std::vector<std::string> arg, int argSize);

            /**
             * @brief Launch User Command
             * 
             * @param arg 
             * @param argSize 
             */

            void launchUser(std::shared_ptr<Client>, std::vector<std::string> arg, int argSize);

            /**
             * @brief QUIT the FTP Shell
             * 
             * @param arg 
             * @param argSize 
             */

            void launchQuit(std::shared_ptr<Client>, std::vector<std::string> arg, int argSize);

            /**
             * @brief launch PASS Command
             * 
             * @param arg 
             * @param argSize 
             */

            void launchPass(std::shared_ptr<Client>, std::vector<std::string> arg, int argSize);

        /**
         * @brief add All logins to a map
         * 
         */

            void fillLoggin(void);


            static boost::shared_ptr<Ftp> create();


        protected:
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
        std::vector<boost::shared_ptr<IModule>> _moduleArray;
        std::vector<std::shared_ptr<Client>> _clientArray;
        std::unordered_map<std::string, void (Ftp::*)(std::shared_ptr<Client>, std::vector<std::string>, int argSize)> _functionMap;
        std::unordered_map<std::string, std::string> _mapLoggin;
        std::string _loginPath;
        bool _isAnonymous;
    };
}
#endif /* !FTP_HPP_ */
