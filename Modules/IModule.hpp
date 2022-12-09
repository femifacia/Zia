/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** IModule
*/

#ifndef IMODULE_HPP_
#define IMODULE_HPP_

#include <iostream>
#include <boost/dll/import.hpp>
#include <boost/dll/alias.hpp>
#include "../src/HttpRequest/HttpRequest.hpp"
#include <map>
#include <filesystem>

static std::map<std::string, std::string> code = {
    // Inforamtion
    {"100", "100 Continue"},
    {"101", "101 Switching Protocols"},

    // Sucessful responses
    {"200", "200 OK"},
    {"201", "201 Created"},
    {"202", "202 Accepted"},
    {"203", "203 Non-Authoritative Information"},
    {"204", "204 No Content"},
    {"205", "205 Reset Content"},
    {"206", "206 Partial Content"},

    // Redirection responses
    {"300", "300 Multiple Choices"},
    {"301", "301 Moved Permanently"},
    {"302", "302 Found"},
    {"303", "303 See Other"},
    {"304", "304 Not Modified"},
    {"305", "305 Use Proxy"},
    //    "306": "306", Not used
    {"307", "307 Temporary redirect"},

    // Client side errors
    {"400", "400 Bad Request"},
    {"401", "401 Unauthorized"},
    {"402", "402 Payment Required"},
    {"403", "403 Forbidden"},
    {"404", "404 Not Found"},
    {"405", "405 Method Not Allowed"},
    {"406", "406 Not Acceptable"},
    {"407", "407 Proxy Authentification Required"},
    {"408", "408 Request Timeout"},
    {"409", "409 Conflict"},
    {"410", "410 Gone"},
    {"411", "411 Length Required"},
    {"412", "412 Precondition Failed"},
    {"413", "413 Request Entity Too Large"},
    {"414", "414 Request-URI Too Long"},
    {"415", "415 Unsupported Media Type"},
    {"416", "416 Requested Range Not Satisfiable"},
    {"417", "417 Expectation Failed"},

    // Server side errors
    {"500", "500 Internal Server Error"},
    {"501", "501 Not Implemented"},
    {"502", "502 Bad Gateway"},
    {"503", "503 Service Unavailable"},
    {"504", "504 Gateway Timeout"},
    {"505", "505 HTTP Version Not Supported"},
};

namespace Module {
    class BOOST_SYMBOL_VISIBLE IModule
    {
    public:
        /**
         * @brief The way to call a module when a request is catched
         *
         * @param trigger
         * @param request
         * @param response
         * @param serviceRoot
         */
        virtual void launch(std::string trigger, HttpRequest &request, HttpRequest &response, std::string serviceRoot) = 0;
        
        /**
         * @brief Get the Name object
         *
         * @return string
         */
        virtual std::string getName(void) = 0;

        /**
         * @brief Get the Type object
         *
         * @return int
         */
        virtual int getType(void) = 0;

        /**
         * @brief Init the module if necessary
         *
         */
        virtual int init(std::string) = 0;

        /**
         * @brief Launch the loop of the module if necessary
         *
         */
        virtual void run(void) = 0;

        /**
         * @brief Close the module if necessary
         *
         */
        virtual void close(void) = 0;

        /**
         * @brief Set the Service object
         *
         * @param service
         */
        virtual void setService(void *service) = 0;

        /**
         * @brief Print a message to another module
         * 
         * @param str 
         */
        virtual void print(std::string str) = 0;

    protected:
        /**
         * @brief Lauch the module behavior
         * 
         * @param trigger 
         * @param request 
         * @param response 
         * @param serviceRoot 
         */
        virtual void behavior(std::string trigger, HttpRequest &request, HttpRequest &response, std::string serviceRoot) = 0;
    };
}

#endif /* !IMODULE_HPP_ */
