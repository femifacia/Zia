/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** Ssl
*/

#include "SSL.hpp"

namespace Module {
    void Ssl::setService(void *service)
    {
        _service = (Service *)service;
    }

    void Ssl::close(void)
    {
        _ioContext.stop();
        if (_acceptThread.joinable())
            _acceptThread.join();
        _acceptor.close();
    }

    void Ssl::manageClient(std::shared_ptr<SslConnexion> client)
    {
        boost::system::error_code ec;
        int size = 0;
        std::vector<char> buffer(2048);
        std::string message;
        
        message = client->read();
        HttpRequest request(message), response;
    }

    void Ssl::run(void)
    {
        _acceptMutex.lock();
        _acceptMutex.unlock();
    }

    std::string Ssl::getPassword(void) const
    {
        return ("test");
    }

    void Ssl::addConnection(std::shared_ptr<SslConnexion> connection)
    {
        _sslConnexionArray.push_back(connection);
    }

    void Ssl::handleAccept(std::shared_ptr<SslConnexion> connection, const boost::system::error_code &error)
    {
        _acceptMutex.lock();
        if (!error)
        {
            _moduleArray = _service->getModuleArray();
            connection->setModuleArray(_moduleArray);
            connection->setReadMutex(&_readMutex);
            connection->setRoot(_service->getRoot());
            connection->startHandshake();
            addConnection(connection);
            print("client accepted");
        }
        else
        {
            print("Client rejected");
        }
        _acceptMutex.unlock();
        acceptClient();
    }

    void Ssl::acceptClient(void)
    {
        std::shared_ptr<SslConnexion> connexion(new SslConnexion(_ioContext, _context));

        _acceptor.async_accept(connexion->getSocket(),
                            boost::bind(&Ssl::handleAccept, this, connexion,
                                        boost::asio::placeholders::error));
    }

    int Ssl::init(std::string)
    {
        if (!_service) {
            std::cout << "[Ssl Module] Initialization impossible beacause no service has been linked to me sah" << std::endl;
            return 0;
        }
        try {
            _context.set_options(
                boost::asio::ssl::context::default_workarounds | boost::asio::ssl::context::no_sslv2 | boost::asio::ssl::context::sslv23 | boost::asio::ssl::context::single_dh_use);
            _context.set_password_callback(boost::bind(&Ssl::getPassword, this));
            _context.use_certificate_chain_file(_permFile);
            _context.use_private_key_file(_keyFile, boost::asio::ssl::context::pem);
            boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), _service->getPort());
            _acceptor.open(endpoint.protocol());
            _acceptor.bind(endpoint);
            _acceptor.listen();
            acceptClient();
            _moduleArray = _service->getModuleArray();
            _acceptThread = std::thread([this]()
                                        { _ioContext.run(); });
        } catch (std::exception &ex) {
            std::cerr << ex.what() << std::endl;
            return (0);
        }
        return (1);
    }

    std::string Ssl::getName(void)
    {
        return (_name);
    }

    int Ssl::getType(void)
    {
        return (_type);
    }

    void Ssl::launch(std::string trigger, HttpRequest &request, HttpRequest &response, std::string serviceRoot)
    {
    }

    void Ssl::behavior(std::string trigger, HttpRequest &request, HttpRequest &response, std::string serviceRoot)
    {
    }

    Ssl::Ssl() : _acceptor(_ioContext), _context(boost::asio::ssl::context::sslv23)
    {
        _name = "Ssl";
        _type = 1;
        _service = NULL;
        _permFile = "../Modules/SSL/perm/ca.pem";
        _keyFile = "../Modules/SSL/perm/key.pem";
    }

    Ssl::~Ssl()
    {
    }

    void Ssl::print(std::string str)
    {
        if (!_service) {
            std::cout << "[" << _name << "]: " << str << std::endl;
            _service->writeLog("[" + _name + "]: " + str);
        } else
            _service->writeLog("[" + _service->getName() + " " + _name + "]: " + str);
    }

    boost::shared_ptr<Ssl> Ssl::create()
    {
        return boost::shared_ptr<Ssl>(
            new Ssl());
    }
}

BOOST_DLL_ALIAS(
    Module::Ssl::create,
    createModule)
