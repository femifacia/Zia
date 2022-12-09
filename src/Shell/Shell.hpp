/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** Shell
*/

#ifndef SHELL_HPP_
#define SHELL_HPP_

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include "boost/asio.hpp"
#include <unordered_map>
#include <vector>


class Shell {
    public:

    /**
     * @brief Launch reloading of the conf file (zia.ini)
     * 
     */

    void launchReload(void);

    /**
     * @brief quit the shell
     * 
     */

    void launchQuit(void);

    /**
     * @brief Split a string into a Vector
     * 
     * @param str 
     * @param delim 
     * @return std::vector<std::string> 
     */

    std::vector<std::string> spliter(std::string str, std::string delim);

    /**
     * @brief Manage the input
     * 
     * @param input 
     */

    void manageInput(std::string input);

    /**
     * @brief stop the server
     * 
     */

    void stop();

    /**
     * @brief return 1 if the shell can continue otherwise 0
     * 
     * @return true 
     * @return false 
     */

    bool isRunning(void);

    /**
     * @brief Set the Running object
     * 
     */

    void setRunning(bool);

    /**
     * @brief run the shell
     * 
     */

    void run(void);

    /**
     * @brief Set the Core object
     * 
     * @param core 
     */

    void setCore(void *core);

    /**
     * @brief Construct a new Shell object
     * 
     */
        Shell();
        /**
         * @brief Destroy the Shell object
         * 
         */
        ~Shell();
        /**
         * @brief Get the Input on the standard Input
         * 
         * @return std::string 
         */
        std::string getInput(void);

        /**
         * @brief print a message
         * 
         */
        void print(std::string);

        /**
         * @brief 
         * 
         * @param arg 
         * @param argSize 
         */

        void printHelp(std::vector<std::string> arg, int argSize);

        /**
         * @brief load a module for a service
         * 
         * @param arg 
         * @param argSize 
         */

        void loadModule(std::vector<std::string> arg, int argSize);

        /**
         * @brief unload a module for a service
         * 
         * @param arg 
         * @param argSize 
         */

        void unloadModule(std::vector<std::string> arg, int argSize);

        /**
         * @brief list all modules on each service
         * 
         * @param arg 
         * @param argSize 
         */

        void launchList(std::vector<std::string> arg, int argSize);

        /**
         * @brief Set the Conf Path object
         * 
         * @param arg 
         * @param argSize 
         */

        void setConfPath(std::vector<std::string> arg, int argSize);

        /**
         * @brief 
         * 
         * @param arg 
         * @param argSize 
         */
        void printConfPath(std::vector<std::string> arg, int argSize);

        /**
         * @brief 
         * 
         * @param arg 
         * @param argSize 
         */

        void printLog(std::vector<std::string> arg, int argSize);
    protected:
    private:
        void *_core;
        std::string _shellName;
        bool _isRunning;
        std::mutex _signalMutex;
        boost::asio::io_service _ioService;
        boost::asio::signal_set _signal;
        std::thread _shellThread;
        std::unordered_map<std::string, void (Shell::*)(std::vector<std::string>, int argSize)> _functionMap;
};

Shell *saveShell(Shell *data);
void stopShell(const boost::system::error_code &error, int sig);

#endif /* !SHELL_HPP_ */
