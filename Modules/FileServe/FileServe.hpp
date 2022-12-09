/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** FileServe
*/

#ifndef FILESERVE_HPP_
#define FILESERVE_HPP_

#include "../IModule.hpp"
#include "../../src/HttpRequest/HttpRequest.hpp"
#include "../../src/Service/Service.hpp"
#include <fstream>
#include <unordered_map>
#include <filesystem>
#include <sys/stat.h>

namespace Module {
    class FileServe : public IModule
    {
    public:
        /**
         * @brief Construct a new File Serve object
         * 
         */
        FileServe();

        /**
         * @brief Destroy the File Serve object
         * 
         */
        ~FileServe();

        /**
         * @brief Launch the module
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
         * @brief Create a new FileServe object with factory method
         * 
         * @return boost::shared_ptr<FileServe> 
         */
        static boost::shared_ptr<FileServe> create();

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
         * @brief Lauch the module behavior
         * 
         * @param trigger 
         * @param request 
         * @param response 
         * @param serviceRoot 
         */
        void behavior(std::string trigger, HttpRequest &request, HttpRequest &response, std::string serviceRoot);
    private:
        std::unordered_map<std::string, std::string> _mimeTypes;
        int _type;
        std::string _name;
        Service *_service;
        std::map<std::string, void (FileServe::*)(HttpRequest&, HttpRequest&, std::string)> _functionMap;
};
}

#endif /* !FILESERVE_HPP_ */
