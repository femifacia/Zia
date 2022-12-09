/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** Client
*/

#include "Client.hpp"

void Client::close(void)
{
    _tcpConnection->close();
    _isConnected = 0;
    //std::cout << "CLOSING" << std::endl;
}

boost::asio::ip::tcp::socket &Client::getSocket(void)
{
    return (_tcpConnection->getSocket());
}

void Client::sendMessage(std::string message)
{
    _tcpConnection->sendMessage(message);
}

TcpConnection::boostPtr Client::getTcpConnection(void)
{
    return (_tcpConnection);
}

bool Client::isConnected(void)
{
    if (!_tcpConnection->getSocket().is_open())
        return (0);
    return (_isConnected);
}

int Client::bytesAvailables(void)
{
    if (!_isConnected)
        return (0);
    return (_tcpConnection->getSocket().available());
}

std::string Client::getName(void)
{
    return (_name);
}

void Client::setName(std::string name)
{
    _name = name;
}

void Client::setIsConnected(bool value)
{
    _isConnected = value;
}


void Client::setLoggingStatus(LOGGING_STATUS status)
{
    _loggingStatus = status;
}

LOGGING_STATUS Client::getLoggingStatus(void)
{
    return (_loggingStatus);
}

void Client::setPassword(std::string pass)
{
    _password = pass;
}

std::string Client::getPassword(void)
{
   return (_password);
}

Client::Client(TcpConnection::boostPtr tcpConnection): _tcpConnection(tcpConnection)
{
    _isConnected = 1;
    _name = "";
    _loggingStatus = NOT_LOGGED;
    _password = "";
}

Client::~Client()
{
}
