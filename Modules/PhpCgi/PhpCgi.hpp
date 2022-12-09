/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** PhpCgi
*/

#ifndef PHPCGI_HPP_
#define PHPCGI_HPP_
#define BOOST_DLL_FORCE_ALIAS_INSTANTIATION

#include "../IModule.hpp"
#include "../../src/HttpRequest/HttpRequest.hpp"
#include "../../src/Service/Service.hpp"
#include <iostream>
#include <fstream>

namespace Module {
    class PhpCgi : public IModule
    {
    public:
        /**
         * @brief Construct a new Php Cgi object
         * 
         */
        PhpCgi();

        /**
         * @brief Destroy the Php Cgi object
         * 
         */
        ~PhpCgi();

        /**
         * @brief Lauch the Module behavoir
         * 
         * @param trigger 
         * @param request 
         * @param response 
         * @param serviceRoot 
         */
        void launch(std::string trigger, HttpRequest &request, HttpRequest &response, std::string serviceRoot);
        
        /**
         * @brief Get the Name object
         * 
         * @return std::string 
         */
        std::string getName(void);

        /**
         * @brief Get the Type object
         * 
         * @return int 
         */
        int getType(void);

        /**
         * @brief init the module if necessary
         * 
         */
        int init(std::string);

        /**
         * @brief launch the loop of the module if necessary
         * 
         */
        void run(void);

        /**
         * @brief close the module if necessary
         * 
         */
        void close(void);

        /**
         * @brief Set the Service object
         * 
         * @param service 
         */
        void setService(void *service);


        /**
         * @brief Create a new PhpCgi object with factory method
         * 
         * @return boost::shared_ptr<PhpCgi> 
         */
        static boost::shared_ptr<PhpCgi> create();

        /**
         * @brief Send a message to another module
         * 
         * @param str 
         */
        void print(std::string str);

        /**
         * @brief GET request
         * 
         * @param request 
         * @param response 
         * @param serviceRoot 
         * @return ** void 
         */
        void get(HttpRequest& request, HttpRequest& response, std::string serviceRoot);

        /**
         * @brief HEAD request
         * 
         * @param request 
         * @param response 
         * @param serviceRoot 
         * @return ** void 
         */
        void head(HttpRequest& request, HttpRequest& response, std::string serviceRoot);

        /**
         * @brief OPTIONS request
         * 
         * @param request 
         * @param response 
         * @param serviceRoot 
         * @return ** void 
         */
        void options(HttpRequest& request, HttpRequest& response, std::string serviceRoot);

    protected:
        /**
         * @brief Launch the module behavior
         * 
         * @param trigger 
         * @param request 
         * @param response 
         * @param serviceRoot 
         */
        void behavior(std::string trigger, HttpRequest &request, HttpRequest &response, std::string serviceRoot);

    private:
        int _type;
        std::string _name;
        Service *_service;
        std::map<std::string, void (PhpCgi::*)(HttpRequest&, HttpRequest&, std::string)> _functionMap;
    };
}

#endif /* !PHPCGI_HPP_ */
