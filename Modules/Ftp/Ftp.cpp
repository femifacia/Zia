/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** Ftp
*/

#include "Ftp.hpp"

namespace Module {

    Ftp::~Ftp()
    {
    }

    void Ftp::print(std::string str)
    {
        if (!_service) {
            std::cout << "[" << _name << "]: " << str << std::endl;
            _service->writeLog( "[" + _name + "]: " + str );
        /* _logger = _service->getLogger();
            if (_logger) {
                (*_logger) << "[" << _name << "]: " << str << std::endl;
            }*/
        }
        else {
            _service->writeLog("[" + _service->getName() + " " + _name + "]: " + str );
            std::cout << "[" + _service->getName() + " " + _name + "]: " + str << std::endl;
        /* _logger = _service->getLogger();
            if (_logger)
                (*_logger) << "okkkk";  */
                //(*_logger) << "["<< _service->getName() <<" " << _name << "]: " << str << std::endl;
        }
    }

    void Ftp::setService(void *service)
    {
        _service = (Service *)service;
    }

    void Ftp::close(void)
    {
        _ioContext.stop();
        if (_acceptThread.joinable())
            _acceptThread.join();
        _acceptor.close();
    }

    void Ftp::run(void)
    {
        _acceptMutex.lock();
        for (std::shared_ptr<Client> client: _clientArray) {
            manageClient(client);
        }
        closeAllConnection();
        _acceptMutex.unlock();
    }



    int Ftp::init(std::string)
    {
        if (!_service) {
            std::cout << "[Ftp Module] Initialization impossible beacause no service has been linked to me sah" << std::endl;
            return 0;
        }
        try {
            //std::cout << "sahhhhh" << _service->getPort() << std::endl;
            //std::cout << "nbr instance" <<_nbrInstance<< std::endl;
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
            //print("Fail ... I am not running");
            //while (isRunning());
            //close();
        }
        return (1);
    }

    void Ftp::handleAccept(TcpConnection::boostPtr newConnection, const boost::system::error_code& error)
    {

        _acceptMutex.lock();
        if (!error) {
            //addClient(newConnection);
            //_socketArr.push_back(newConnection);
            //_hostsConneted += 1;
            print("New Client Accepted");
            addClient(newConnection);
        //std::cout << request.generate() << std::endl;
            //newConnection->sendMessage(request.generate());
            //newConnection->close();
            //newConnection->sendMessage("HTTP/1.1 200 OK\nContent-Length: 14\nContent-Type:text /plain\n\nHello world! pm");
        } else
            print("New Client Rejected");
        _acceptMutex.unlock();
        acceptClient();
    }

    void Ftp::acceptClient(void)
    {
        TcpConnection::boostPtr newConnection = TcpConnection::createBoostPtr(_ioContext);

        _acceptor.async_accept(newConnection->getSocket(), boost::bind(&Ftp::handleAccept, this, newConnection, boost::placeholders::_1));
    }

    void Ftp::cleanFtpRequest(std::string &str)
    {
        int size = str.size();
        std::string stri = str;


        for (int i = 0; i < size; i++) {
            if (stri[i] == '\r' || stri[i] == '\n')
                stri[i] = '\0';
        }
        str = "";
        for (int i = 0; stri[i] != '\0'; i++)
            str += stri[i];
    }

    std::vector<std::string> Ftp::spliter(std::string str, std::string delim)
    {
        std::size_t pos = 0;
        std::string token = "";
        std::vector<std::string> vec = {};

        if (str == "") {
            vec.push_back("");
            return (vec);
        }
        while ((pos = str.find(delim)) != std::string::npos)
        {
            token = str.substr(0, pos);
            if (token != "")
                vec.push_back(token);
            str.erase(0, pos + delim.length());
        }
        if (str != "")
            vec.push_back(str);
        return (vec);
    }

    void Ftp::manageClient(std::shared_ptr<Client> client)
    {
        boost::system::error_code ec;
        int bytess = client->bytesAvailables();
        std::vector<char> buffer(bytess);
        std::string message;
        int size = 0;
        int argSize = 0;
        void (Ftp::*ptr)(std::shared_ptr<Client>, std::vector<std::string>, int argSize);

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
        cleanFtpRequest(message);
        std::vector<std::string> arg = spliter(message, " ");
        argSize = arg.size();
        if (message == "" ||! arg.size()) {
            if (client->getLoggingStatus() != LOGGED)
                client->sendMessage("[NOT LOGGED] ");
            else
                client->sendMessage("[" + client->getName() + "] ");
            return;
        }
        ptr = _functionMap[arg[0]];
        if (ptr)
            (this->*ptr)(client, arg, argSize);
        else
            client->sendMessage("500 Wrong command.\r\n");
        if (client->getLoggingStatus() != LOGGED)
            client->sendMessage("[NOT LOGGED] ");
        else
            client->sendMessage("[" + client->getName() + "] ");
        //std::cout << "!"<< message <<"!"<< std::endl;
    }

    void Ftp::closeAllConnection(void)
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

    void Ftp::addClient(TcpConnection::boostPtr connection)
    {
        std::shared_ptr<Client> client(new Client(connection));

        _clientArray.push_back(client);
        client->sendMessage("220 Service ready for new user.\r\n");
        if (!_isAnonymous) {
            client->sendMessage("220 No anonymous access.\r\n");
            client->sendMessage("220 user USER and PASS command to log in.\r\n");
        }
        client->sendMessage("[NOT LOGGED] ");
    }


    std::string Ftp::getName(void)
    {
        return (_name);
    }

    int Ftp::getType(void)
    {
        return (_type);
    }

    void Ftp::launch(std::string trigger, HttpRequest &request, HttpRequest &response, std::string serviceRoot)
    {
    }

    void Ftp::behavior(std::string trigger, HttpRequest &request, HttpRequest &response, std::string serviceRoot)
    {
    }

    void Ftp::launchQuit(std::shared_ptr<Client> client, std::vector<std::string> arg, int argSize)
    {
        client->sendMessage("221 Service closing control connection.\r\n");
        print("User " + client->getName() + " Logged Out");
        client->close();
    }

    void Ftp::launchUser(std::shared_ptr<Client> client, std::vector<std::string> arg, int argSize)
    {
        LOGGING_STATUS status;

        if (argSize != 2) {
            client->sendMessage("500 Error Syntax! You have to enter 2 args.\r\n");
            return;
        }
        status = client->getLoggingStatus();
        if ( status == LOGGED) {
            client->sendMessage("530 Can't change from guest user.\r\n");
            return;
        }
        client->setName(arg[1]);
        if (status == NOT_LOGGED) {
            client->sendMessage("331 User name okay, need password.\r\n");
            client->setLoggingStatus(IN_PROCESS);
            return;
        }
        if (status == IN_PROCESS) {
            if (_mapLoggin[arg[1]] != client->getPassword()) {
                client->sendMessage("530 Bad login user / pass.\r\n");
                return;
            } else {
                client->sendMessage("230 User logged in, proceed.\r\n");
                client->setLoggingStatus(LOGGED);
                print(client->getName() + " Logged In");
            }
        }
    }

    void Ftp::launchHelp(std::shared_ptr<Client> client, std::vector<std::string> arg, int argSize)
    {
        std::string message = "214 Commands availables USER PASS QUIT EXIT HELP.";

        message += "\r\n";
        client->sendMessage(message);
    }


    void Ftp::launchPass(std::shared_ptr<Client> client, std::vector<std::string> arg, int argSize)
    {
        LOGGING_STATUS status;

        if (argSize > 2) {
            client->sendMessage("500 Error Syntax! You have to enter 2 args.\r\n");
            return;
        }
        status = client->getLoggingStatus();
        if ( status == LOGGED) {
            client->sendMessage("530 Can't change from guest user.\r\n");
            return;
        }
        if (argSize == 2)
            client->setPassword(arg[1]);
        else
            client->setPassword("");
        if (status == NOT_LOGGED) {
            client->sendMessage("332 Need account for login.\r\n");
            client->setLoggingStatus(IN_PROCESS);
            return;
        }
        if (status == IN_PROCESS) {
            if (_mapLoggin[client->getName()] != client->getPassword()) {
                client->sendMessage("530 Bad login user / pass.\r\n");
                return;
            } else {
                client->sendMessage("230 User logged in, proceed.\r\n");
                client->setLoggingStatus(LOGGED);
                print(client->getName() + " Logged In");
            }
        }
    }

    void Ftp::fillLoggin(void)
    {
        std::ifstream file(_loginPath);
        std::string line;

        if (!file.is_open()) {
            _mapLoggin["Anonymous"] = "";
            return;
        }
        while (std::getline(file, line)) {
            std::vector<std::string> arg = spliter(line, " ");
            if (arg.size() != 2)
                continue;
            _isAnonymous = 0;
            _mapLoggin[arg[0]] = arg[1];
        }
    }

    Ftp::Ftp():_acceptor(_ioContext)
    {
        _isAnonymous = 1;
        _type = 1;
        _name = "Ftp";
        _service = NULL;
        _loginPath = "../Modules/Ftp/login.txt";
        //td::cout << "PENIS" << std::endl;
        _nbrInstance ++;
        _functionMap["USER"] = &Ftp::launchUser;
        _functionMap["QUIT"] = &Ftp::launchQuit;
        _functionMap["EXIT"] = &Ftp::launchQuit;
        _functionMap["HELP"] = &Ftp::launchHelp;
        _functionMap["PASS"] = &Ftp::launchPass;

        fillLoggin();
    // _logger = NULL;
    
    }

    int Ftp::_nbrInstance = 0;

    boost::shared_ptr<IModule> Ftp::newPtr(void)
    {
        boost::shared_ptr<IModule> mod(new Ftp());

        return (mod);
    }

    int Ftp::getNbrInstances(void)
    {
        return (_nbrInstance);
    }


    boost::shared_ptr<Ftp> Ftp::create() {
        return boost::shared_ptr<Ftp>(
            new Ftp()
            );
    }
}
BOOST_DLL_ALIAS(
    Module::Ftp::create,
    createModule
)