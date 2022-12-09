/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** SslConnexion
*/

#ifndef SSLCONNEXION_HPP_
#define SSLCONNEXION_HPP_

//#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include "../../../src/Service/Service.hpp"
#include "../../../src/HttpRequest/HttpRequest.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/system/error_code.hpp>

typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> SslSocket;

class SslConnexion :public boost::enable_shared_from_this<SslConnexion>{
    public:

    void setRoot(std::string root);

    void setReadMutex(std::mutex *mutex);

    void handleWrite(const boost::system::error_code &);

    void handleRead(const boost::system::error_code& error, size_t bytes_transferred);

    void setModuleArray(std::vector<boost::shared_ptr<Module::IModule>> moduleArray);

    /**
     * @brief read the content of the socket
     * 
     * @return std::string 
     */

    std::string read(void);

    /**
     * @brief return the nbr of bytes availables
     * 
     * @return int 
     */

    int bytesAvailable(void);

    /**
     * @brief The handler called at the end of the handshake step
     * 
     * @param error 
     */

    void handleHandshake(const boost::system::error_code& error);

    /**
     * @brief Start Handshake step. Here we send our certificates and to client and get his response for them
     * 
     */

    void startHandshake(void);

    /**
     * @brief Get the Socket object
     * 
     * @return SslSocket::lowest_layer_type& 
     */

    SslSocket::lowest_layer_type& getSocket();


    /**
     * @brief Construct a new Ssl Connexion object
     * 
     * @param ioContext 
     * @param sslContext 
     */
        SslConnexion(boost::asio::io_context &ioContext, boost::asio::ssl::context &sslContext);
    /**
     * @brief Destroy the Ssl Connexion object
     * 
     */
        ~SslConnexion();

    protected:
    private:
    SslSocket _socket;
    char _data[2048];
    std::vector<boost::shared_ptr<Module::IModule>> _moduleArray;
    std::mutex *_readMutex;
    std::string _root;
    std::string _finalResponse;
};

#endif /* !SSLCONNEXION_HPP_ */
