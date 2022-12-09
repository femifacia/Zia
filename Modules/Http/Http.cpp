/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** Http
*/

#include "Http.hpp"

namespace Module {
    void Http::print(std::string str)
    {
        if (!_service) {
            std::cout << "[" << _name << "]: " << str << std::endl;
            _service->writeLog( "[" + _name + "]: " + str );
        } else
            _service->writeLog("[" + _service->getName() + " " + _name + "]: " + str );
    }

    void Http::setService(void *service)
    {
        _service = (Service *)service;
    }

    void Http::close(void)
    {
        _ioContext.stop();
        if (_acceptThread.joinable())
            _acceptThread.join();
        _acceptor.close();
    }

    void Http::run(void)
    {
        _acceptMutex.lock();
        for (std::shared_ptr<Client> client: _clientArray)
            manageClient(client);
        closeAllConnection();
        _acceptMutex.unlock();
    }

    int Http::init(std::string)
    {
        if (!_service) {
            std::cout << "[HTTP Module] Initialization impossible beacause no service has been linked to me sah" << std::endl;
            return 0;
        }
        try {
            boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), _service->getPort());
            _endpoint = endpoint;
            _acceptor.open(_endpoint.protocol());
            _acceptor.bind(_endpoint);
            _acceptor.listen();
            acceptClient();
            _moduleArray = _service->getModuleArray();
            _acceptThread = std::thread([this]() { _ioContext.run(); });
        } catch (std::exception& ex) {
            std::cerr << ex.what() << std::endl;
            std::cout << std::string("Port " + std::to_string(_service->getPort()) + " is Already used") << std::endl;
            return (0);
        }
        return (1);
    }

    void Http::handleAccept(TcpConnection::boostPtr newConnection, const boost::system::error_code& error)
    {

        _acceptMutex.lock();
        if (!error) {
            print("New Client Accepted");
            addClient(newConnection);
        } else
            print("New Client Rejected");
        _acceptMutex.unlock();
        acceptClient();
    }

    void Http::acceptClient(void)
    {
        TcpConnection::boostPtr newConnection = TcpConnection::createBoostPtr(_ioContext);

        _acceptor.async_accept(newConnection->getSocket(), boost::bind(&Http::handleAccept, this, newConnection, boost::placeholders::_1));
    }

    void Http::manageClient(std::shared_ptr<Client> client)
    {
        boost::system::error_code ec;
        int bytess = client->bytesAvailables();
        std::vector<char> buffer(bytess);
        std::string message;
        int size = 0;

        if (bytess == 0)
            return;
        while (bytess) {
            client->getSocket().read_some(boost::asio::buffer(buffer.data(), buffer.size()), ec);
            for (char c : buffer)
                message.append(1, c);
            size = buffer.size();
            for (int i = 0; i < size; i++)
                buffer[i] = '\0';
            bytess = client->bytesAvailables();
        }

        HttpRequest request(message), response;

        _moduleArray = _service->getModuleArray();
        if (_service) {
            for (boost::shared_ptr<IModule> ptr: _moduleArray)
                ptr->launch("", request, response, _service->getRoot());
        }
        client->sendMessage(response.generate());
        client->close();
    }

    void Http::closeAllConnection(void)
    {
        int i = 0;
        int clientSize = 0;

        clientSize = _clientArray.size();
        while (i < clientSize) {
            for (i = 0; i < clientSize; i++) {
                if (!_clientArray[i]->isConnected()) {
                    _clientArray[i]->close();
                    _clientArray.erase(_clientArray.begin() + i);
                    break;
                }
            }
            clientSize = _clientArray.size();
        }
    }

    void Http::addClient(TcpConnection::boostPtr connection)
    {
        std::shared_ptr<Client> client(new Client(connection));

        _clientArray.push_back(client);
    }


    std::string Http::getName(void)
    {
        return (_name);
    }

    int Http::getType(void)
    {
        return (_type);
    }

    void Http::launch(std::string trigger, HttpRequest &request, HttpRequest &response, std::string serviceRoot)
    {
    }

    void Http::behavior(std::string trigger, HttpRequest &request, HttpRequest &response, std::string serviceRoot)
    {
    }

    Http::Http():_acceptor(_ioContext)
    {
        _type = 1;
        _name = "http";
        _service = NULL;
    }

    Http::~Http()
    {
    }

    boost::shared_ptr<Http> Http::create() {
        return boost::shared_ptr<Http>(
            new Http()
            );
    }
}

BOOST_DLL_ALIAS(
    Module::Http::create,
    createModule
)
