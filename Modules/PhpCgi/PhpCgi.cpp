/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** PhpCgi
*/

#include "PhpCgi.hpp"

namespace Module {
    void PhpCgi::setService(void *service)
    {
        _service = (Service *)service;
    }

    void PhpCgi::close(void)
    {
    }

    void PhpCgi::run(void)
    {
    }

    int PhpCgi::init(std::string)
    {
        return (1);
    }

    std::string PhpCgi::getName(void)
    {
        return (_name);
    }

    int PhpCgi::getType(void)
    {
        return (_type);
    }

    void PhpCgi::launch(std::string trigger, HttpRequest &request, HttpRequest &response, std::string serviceRoot)
    {
        std::string arg = request.getArgument();
        int e = arg.find(".php");

        if ((e != std::string::npos && e + 4 == arg.size()))
            behavior("", request, response, serviceRoot);

        if (arg == "/" && std::filesystem::exists(serviceRoot + "index.php"))
            behavior("", request, response, serviceRoot);
    }

    void PhpCgi::behavior(std::string trigger, HttpRequest &request, HttpRequest &response, std::string serviceRoot)
    {
        std::vector<std::string> vec = {};
        std::string content = "";
        std::string path = serviceRoot + "index.html";
        std::string codeRoot = "../Modules/error/";
        void (PhpCgi::*ptr)(HttpRequest &, HttpRequest &, std::string);
        std::ifstream file("");

        response.setField("Content-Type", "text/html; charset=UTF-8");
        if (request.getStatus() == "400") {
            file.close();
            file.open(codeRoot + "400error.html");
            getline(file, content, '\0');
            response.setType("HTTP/1.1 " + code["400"]);
            response.setBody(content);
            file.close();
            return;
        }

        if (request.getArgument() != "/") {
            boost::split(vec, request.getArgument(), boost::is_any_of("/"));
            path = serviceRoot + vec[vec.size() - 1];

            std::ifstream file(path);
            if (!file.good()) {
                file.close();
                file.open(codeRoot + "404error.html");
                getline(file, content, '\0');
                response.setType("HTTP/1.1 " + code["404"]);
                response.setBody(content);
                file.close();
                return;
            }
            if (!std::filesystem::is_regular_file(path)) {
                file.close();
                file.open(codeRoot + "403error.html");
                getline(file, content, '\0');
                response.setType("HTTP/1.1 " + code["403"]);
                response.setBody(content);
                return;
            }
        }
        ptr = _functionMap[request.getType()];
        if (ptr)
            (this->*ptr)(request, response, serviceRoot);
        print(request.getType() + " " + request.getArgument() + "HTTP/1.1" + response.getType());
        std::remove("temp.txt");
    }

    void PhpCgi::get(HttpRequest &request, HttpRequest &response, std::string serviceRoot)
    {
        std::vector<std::string> vec = {};
        std::string content = "";
        std::string path = serviceRoot + "index.php";

        if (request.getArgument() != "/")
        {
            boost::split(vec, request.getArgument(), boost::is_any_of("/"));
            path = serviceRoot + vec[vec.size() - 1];
        }
        system(("php-cgi " + path + " > temp.txt").c_str());
        std::ifstream file("temp.txt");
        std::getline(file, content, '\0');
        content.erase(0, content.find("\n") + 1);
        response.setType("HTTP/1.1 " + code["200"]);
        response.setBody(content);
    }

    void PhpCgi::head(HttpRequest &request, HttpRequest &response, std::string serviceRoot)
    {
        response.setType("HTTP/1.1 " + code["200"]);
        response.setField("Server", "nginx/1.15.5 (Ubuntu)");
        response.setField("Date", "Sun, 06 Mar 2022 14:21:44 GMT");
        response.setField("Connection", "keep-alive");
        response.setField("Expires", "Thu, 19 Nov 1981 08:52:00 GMT");
        response.setField("Cache-Control", "no-store, no-cache, must-revalidate");
        response.setField("Pragma", "no-cache");
        response.setField("Content-Encoding", "gzip");
    }

    void PhpCgi::options(HttpRequest &request, HttpRequest &response, std::string serviceRoot)
    {
        response.setType("HTTP/1.1 " + code["200"]);
        response.setField("allow", "OPTIONS, GET, HEAD, POST");
    }


    PhpCgi::PhpCgi()
    {
        _name = "PhpCgi";
        _type = 2;

        _functionMap["GET"] = &PhpCgi::get;
        _functionMap["HEAD"] = &PhpCgi::head;
        _functionMap["OPTIONS"] = &PhpCgi::options;
    }

    PhpCgi::~PhpCgi()
    {
    }

    void PhpCgi::print(std::string str)
    {
        if (!_service) {
            std::cout << "[" << _name << "]: " << str << std::endl;
            _service->writeLog("[" + _name + "]: " + str);
        } else {
            _service->writeLog("[" + _service->getName() + " " + _name + "]: " + str);
        }
    }

    boost::shared_ptr<PhpCgi> PhpCgi::create()
    {
        return boost::shared_ptr<PhpCgi>(
            new PhpCgi());
    }
}

BOOST_DLL_ALIAS(
    Module::PhpCgi::create,
    createModule)