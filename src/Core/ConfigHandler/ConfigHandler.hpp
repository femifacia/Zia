/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** ConfigHandler
*/

#ifndef CONFIGHANDLER_HPP_
#define CONFIGHANDLER_HPP_

#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include "../../Service/Service.hpp"

struct MyModule
{
  std::string path;
  std::vector<std::string> modules;
};

struct ServiceData
{
  std::string name;
  std::string networkModuleName;
  std::string loggerModuleName;
  std::string root;
  int port;
};

struct ConfigData
{
  bool isErr;
  MyModule mod;
  std::vector<ServiceData> services;
};

class ConfigHandler {
    public:
        /**
         * @brief Create the object
         * 
         */
        ConfigHandler();

        /**
         * @brief Destroy the object
         * 
         */
        ~ConfigHandler();

        /**
         * @brief Set the path of the file
         * 
         * @param pathFile 
         * @return ** void 
         */
        void setPathFile(std::string pathFile);

        /**
         * @brief Update configuration data
         * 
         * @return ** void 
         */
        void update();

        /**
         * @brief Set configuration data to default values
         * 
         * @return ** void 
         */
        void defaultUpdate();


        /**
         * @brief Get the Module Path object
         * 
         * @return ** std::string z
         */

        std::string getModulePath() const;


        /**
         * @brief Get the modules
         * 
         * @return ** std::vector<std::string> 
         */
        std::vector<std::string> getModules() const;

        /**
         * @brief Get the services
         * 
         * @return ** std::vector<std::shared_ptr<Service>> 
         */
        std::vector<std::shared_ptr<Service>> getServices() const;

        /**
         * @brief Print all data
         * 
         * @return ** void 
         */
        void printAll();

        /**
         * @brief Print path of the file
         * 
         * @return ** void 
         */
        void printFilePath();

        /**
         * @brief Print path of the module
         * 
         * @return ** void 
         */
        void printModulePath();

        /**
         * @brief Print all modules
         * 
         * @return ** void 
         */
        void printModules();

        /**
         * @brief Print all services
         * 
         * @return ** void 
         */
        void printServices();

    protected:
    private:
        std::string _pathFile;
        std::string _pathModule;
        std::vector<std::string> _moduleArray;
        std::vector<std::shared_ptr<Service>> _serviceArray;

        /**
         * @brief Implementation of std::count function for string
         * 
         * @param begin 
         * @param end 
         * @param elem 
         * @return ** int 
         */
        int counterStr(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end, std::string elem);

        /**
         * @brief Implementation of std::count function for integer
         * 
         * @param begin 
         * @param end 
         * @param elem 
         * @return ** int 
         */ 
        int counterInt(std::vector<int>::iterator begin, std::vector<int>::iterator end, int elem);

        /**
         * @brief Split string using delimiter
         * 
         * @param str 
         * @param delim 
         * @return ** std::vector<std::string> 
         */
        std::vector<std::string> spliter(std::string str, std::string delim);

        /**
         * @brief Check if a string is a number
         * 
         * @param str 
         * @return true 
         * @return false 
         */
        bool isNumber(const std::string str);

        /**
         * @brief Get a more convenient form for file content
         * 
         * @param filename 
         * @return ** std::string 
         */
        std::string getValidContent(char const *filename);

        /**
         * @brief Get information about modules
         * 
         * @param line 
         * @param conf 
         * @return ** void 
         */
        void getModulesInfo(std::string line, ConfigData *conf);

        /**
         * @brief Get information about services
         * 
         * @param line 
         * @param conf 
         * @return ** void 
         */
        void getServicesInfo(std::string line, ConfigData *conf);

        /**
         * @brief Parse file
         * 
         * @param filename 
         * @return ** ConfigData 
         */
        ConfigData parser(char const *filename);

        /**
         * @brief Get configuration file data
         * 
         * @param filename 
         * @return ** ConfigData 
         */
        ConfigData getConfig(char const *filename);
};

#endif /* !CONFIGHANDLER_HPP_ */
