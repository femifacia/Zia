/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** SslConnexion
*/

#include "SslConnexion.hpp"

void SslConnexion::setRoot(std::string root)
{
    _root = root;
}

void SslConnexion::setReadMutex(std::mutex * mutex)
{
    _readMutex = mutex;
}

void SslConnexion::handleWrite(const boost::system::error_code &error)
{
    if (!error)
        getSocket().close();
}

void SslConnexion::handleRead(const boost::system::error_code& error, size_t bytes_transferred)
{
    if (!error) {
    _readMutex->lock();
        HttpRequest request(_data), response;
        for (boost::shared_ptr<Module::IModule> ptr: _moduleArray) {
            ptr->launch("", request, response, _root);
        }
        _finalResponse = response.generate();
    _readMutex->unlock();
        boost::asio::async_write(_socket,
          boost::asio::buffer(_finalResponse),
          boost::bind(&SslConnexion::handleWrite, this,
            boost::asio::placeholders::error));
            
    } else {
        std::cout << "Read procedure didn't work" << std::endl;
    }
}

void SslConnexion::setModuleArray(std::vector<boost::shared_ptr<Module::IModule>> moduleArray)
{
    _moduleArray = moduleArray;
}

std::string SslConnexion::read(void)
{
    boost::system::error_code ec;
    std::vector<char> buffer(2048);
    std::string message;
    int size = 0;

    _socket.read_some(boost::asio::buffer(buffer.data(), buffer.size()), ec);
    for (char c : buffer)
        message.append(1, c);
    return (message);
}

int SslConnexion::bytesAvailable(void)
{
    return (0);
}

void SslConnexion::handleHandshake(const boost::system::error_code& error)
{

    if (!error) {
        _socket.async_read_some(boost::asio::buffer(_data, 2048),
          boost::bind(&SslConnexion::handleRead, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    } else {
    }
}

void SslConnexion::startHandshake(void)
{
    boost::system::error_code error;
    _socket.async_handshake(boost::asio::ssl::stream_base::server,
        boost::bind(&SslConnexion::handleHandshake, this,
          boost::asio::placeholders::error));
}

SslSocket::lowest_layer_type& SslConnexion::getSocket()
{
    return (_socket.lowest_layer());
}

SslConnexion::SslConnexion(boost::asio::io_context &ioContext, boost::asio::ssl::context &sslContext): _socket(ioContext, sslContext)
{
}

SslConnexion::~SslConnexion()
{
}
