/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** HttpRequest
*/

#ifndef HTTPREQUEST_HPP_
#define HTTPREQUEST_HPP_

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <boost/algorithm/string.hpp>

class HttpRequest {
    public:
        HttpRequest(std::string);
        HttpRequest();
        ~HttpRequest();

        std::string getArgument(void) const;
        std::string getStatus(void) const;

        void setType(std::string);
        std::string getType(void) const;
        void setField(std::string, std::string);
        void setBody(std::string);
        std::string generate(void);

    protected:
    private:

        std::string _type;
        std::string _argument;

        std::map<std::string, std::string> _headers;
        std::string _reqBody;
//        std::string _body;

        std::string _resBody;
        std::map<std::string, std::string> _fieldMap;

        std::string _status;

};

#endif /* !HTTPREQUEST_HPP_ */
