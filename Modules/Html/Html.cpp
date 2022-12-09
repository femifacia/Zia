/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** Html
*/

#include "Html.hpp"

namespace Module {
    void Html::setService(void *service)
    {
        _service = (Service *)service;
    }

    void Html::close(void)
    {
    }

    void Html::run(void)
    {
    }

    int Html::init(std::string)
    {
        return (1);
    }

    std::string Html::getName(void)
    {
        return (_name);
    }

    int Html::getType(void)
    {
        return (_type);
    }

    Html::Html()
    {
        _name = "Html";
        _type = 2;

        _functionMap["GET"] = &Html::get;
        _functionMap["HEAD"] = &Html::head;
        _functionMap["OPTIONS"] = &Html::options;
    }

    Html::~Html()
    {
    }

    void Html::launch(std::string trigger, HttpRequest &request, HttpRequest &response, std::string serviceRoot)
    {
        std::string arg = request.getArgument();
        int e = arg.find(".html");

        if ((e != std::string::npos && e + 5 == arg.size()))
            behavior("", request, response, serviceRoot);

        if (arg == "/" && std::filesystem::exists(serviceRoot + "index.html"))
            behavior("", request, response, serviceRoot);
    }

    void Html::behavior(std::string trigger, HttpRequest &request, HttpRequest &response, std::string serviceRoot)
    {
        std::vector<std::string> vec = {};
        std::string content = "";
        std::string path = serviceRoot + "index.html";
        std::string codeRoot = "../Modules/error/";
        void (Html::*ptr)(HttpRequest &, HttpRequest &, std::string);
        std::ifstream file("");

        response.setField("Content-Type", "text/html; charset=UTF-8");
        if (request.getStatus() == "400")
        {
            file.close();
            file.open(codeRoot + "400error.html");
            getline(file, content, '\0');
            response.setType("HTTP/1.1 " + code["400"]);
            response.setBody(content);
            file.close();
            return;
        }

        if (request.getArgument() != "/")
        {
            boost::split(vec, request.getArgument(), boost::is_any_of("/"));
            path = serviceRoot + vec[vec.size() - 1];
            std::ifstream file(path);
            if (!file.good())
            {
                file.close();
                file.open(codeRoot + "404error.html");
                getline(file, content, '\0');
                response.setType("HTTP/1.1 " + code["404"]);
                response.setBody(content);
                file.close();
                return;
            }
            if (!std::filesystem::is_regular_file(path))
            {
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
    }

    void Html::get(HttpRequest &request, HttpRequest &response, std::string serviceRoot)
    {
        std::vector<std::string> vec = {};
        std::string content = "";
        std::string path = serviceRoot + "index.html";

        if (request.getArgument() != "/")
        {
            boost::split(vec, request.getArgument(), boost::is_any_of("/"));
            path = serviceRoot + vec[vec.size() - 1];
        }
        std::ifstream file(path);
        std::getline(file, content, '\0');
        response.setType("HTTP/1.1 " + code["200"]);
        response.setBody(content);
    }

    void Html::head(HttpRequest &request, HttpRequest &response, std::string serviceRoot)
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

    void Html::options(HttpRequest &request, HttpRequest &response, std::string serviceRoot)
    {
        response.setType("HTTP/1.1 " + code["200"]);
        response.setField("allow", "OPTIONS, GET, HEAD, POST");
    }

    void Html::print(std::string str)
    {
        if (!_service) {
            std::cout << "[" << _name << "]: " << str << std::endl;
            _service->writeLog("[" + _name + "]: " + str);
        }
        else
            _service->writeLog("[" + _service->getName() + " " + _name + "]: " + str);
    }

    boost::shared_ptr<Html> Html::create()
    {
        return boost::shared_ptr<Html>(
            new Html());
    }
}

BOOST_DLL_ALIAS(
    Module::Html::create,
    createModule)
