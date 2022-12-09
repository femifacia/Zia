/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** Logger
*/

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include "../IModule.hpp"
#include "../../src/HttpRequest/HttpRequest.hpp"
#include "../../src/Service/Service.hpp"
#include <fstream>
#include <boost/date_time.hpp>
#include <mutex>

namespace Module {
    class Logger : public IModule {
    public:
        /**
         * @brief Construct a new Logger object
         * 
         */
        Logger();

        /**
         * @brief Destroy the Logger object
         * 
         */
        ~Logger();

        /**
         * @brief Launch the module behavior
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
         * @brief Init the module if necessary
         * 
         */
        int init(std::string);

        /**
         * @brief Launch the loop of the module if necessary
         * 
         */
        void run(void);

        /**
         * @brief Close the module if necessary
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
         * @brief Get the Path object
         * 
         * @return ** std::string 
         */
        std::string getPath() const;

        /**
         * @brief Set the Path object
         * 
         * @param path 
         * @return ** void 
         */
        void setPath(std::string path);
 
        /**
         * @brief Get the Mutex object
         * 
         * @return ** std::mutex* 
         */
        std::mutex *getMutex();

        /**
         * @brief  write text at the end of file
         * 
         * @param text 
         * @return ** void 
         */
        void write(std::string text);

        /**
         * @brief Create a new Logger object with factory method
         * 
         * @return boost::shared_ptr<Logger> 
         */
        static boost::shared_ptr<Logger> create();

        /**
         * @brief Send a message to another module
         * 
         * @param str 
         */
        void print(std::string str);

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
     //   Service *_service;

        std::string _path;
        std::mutex _mutex;
    };
}
std::ofstream& operator<<(Module::Logger &logger, std::string message);

#endif /* !LOGGER_HPP_ */
