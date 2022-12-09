/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** TcpConnection
*/

#ifndef TCPCONNECTION_HPP_
#define TCPCONNECTION_HPP_

#include <iostream>
#include <memory>
#include <iostream>
#include <ctime>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/system/error_code.hpp>


class TcpConnection : public boost::enable_shared_from_this<TcpConnection>{
    public:
        typedef boost::shared_ptr<TcpConnection> boostPtr;
        
        static boostPtr createBoostPtr(boost::asio::io_context& ioContext)
        {
            return (boostPtr(new TcpConnection(ioContext)));
        }

    /**
     * @brief Destroy the Tcp Connection object
     * 
     */
        ~TcpConnection();
    /**
     * @brief Get the Socket object
     * 
     * @return asio::ip::tcp::socket& 
     */
        boost::asio::ip::tcp::socket &getSocket(void);
    /**
     * @brief start the connection
     * 
     */
        void start(void);

    /**
     * @brief send a Message to the socket
     * 
     * @param message 
     */
        void sendMessage(std::string message);

    /**
     * @brief the handler for write function
     * 
     */

    void handleWrite(const boost::system::error_code &, size_t);

    /**
     * @brief close the tcpConnection
     * 
     */

    void close(void);


    protected:
    private:
    /**
     * @brief Construct a new Tcp Connection object
     * 
     * @param io_context 
     */
        TcpConnection(boost::asio::io_context &io_context);
        boost::asio::ip::tcp::socket _socket;
        std::string _name;
};

#endif /* !TCPCONNECTION_HPP_ */