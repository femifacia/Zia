/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** TcpConnection
*/

#include "TcpConnection.hpp"


void TcpConnection::close(void)
{
    _socket.close();
}

void TcpConnection::handleWrite(const boost::system::error_code &, size_t)
{
}

boost::asio::ip::tcp::socket &TcpConnection::getSocket(void)
{
    return (_socket);
}


void TcpConnection::sendMessage(std::string message)
{
    boost::asio::async_write(_socket, boost::asio::buffer(message), boost::bind(&TcpConnection::handleWrite, shared_from_this(), boost::placeholders::_1, boost::placeholders::_2));
}

void TcpConnection::start(void)
{
}

TcpConnection::TcpConnection(boost::asio::io_context &io): _socket(io)
{
}


TcpConnection::~TcpConnection()
{
}
