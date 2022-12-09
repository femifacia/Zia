/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include "../TcpConnection/TcpConnection.hpp"

enum LOGGING_STATUS {
    NOT_LOGGED,
    IN_PROCESS,
    LOGGED
};

class Client {
    public:

    /**
     * @brief Destroy the Client object
     * 
     */
        ~Client();

    /**
     * @brief Construct a new Client object
     * 
     */

        Client(TcpConnection::boostPtr);
    /**
     * @brief Get the Tcp Connection object
     * 
     * @return TcpConnection::boostPtr 
     */
        TcpConnection::boostPtr getTcpConnection(void);
    /**
     * @brief Get the Socket object
     * 
     * @return boost::asio::ip::tcp::socket& 
     */
        boost::asio::ip::tcp::socket &getSocket(void);
    /**
     * @brief 
     * 
     */
        void sendMessage(std::string);
    /**
     * @brief Set the Name object
     * 
     * @param name 
     */
        void setName(std::string name);
        /**
         * @brief Get the Name object
         * 
         * @return std::string 
         */
        std::string getName(void);
        /**
         * @brief 
         * 
         * @return int 
         */
        int bytesAvailables(void);
        /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
        bool isConnected(void);
        /**
         * @brief Set the Is Connected object
         * 
         */
        void setIsConnected(bool);

        /**
         * @brief close the socket
         * 
         */
        void close(void);

        /**
         * @brief Set the Loggin Status object
         * 
         * @param status 
         */

        void setLoggingStatus(LOGGING_STATUS status);

        /**
         * @brief Get the Logging Status object
         * 
         * @return LOGGING_STATUS 
         */

        LOGGING_STATUS getLoggingStatus(void);

        /**
         * @brief Set the Password object
         * 
         * @param pass 
         */

        void setPassword(std::string pass);

        /**
         * @brief Get the Password object
         * 
         * @return std::string 
         */

        std::string getPassword(void);

    protected:
    private:
        std::string _name;
        std::string _password;
        TcpConnection::boostPtr _tcpConnection;
        bool _isConnected;
        LOGGING_STATUS _loggingStatus;
};

#endif /* !CLIENT_HPP_ */
