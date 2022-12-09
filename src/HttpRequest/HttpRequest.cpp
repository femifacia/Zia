/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** HttpRequest
*/

#include "HttpRequest.hpp"

HttpRequest::HttpRequest(std::string str)
{
    std::vector<std::string> tempVec = {}, vec = {};
    boost::split(tempVec, str, boost::is_any_of("\n"));
    std::vector<std::string> interm = {};
    std::string temp = "";
    _status = "Good";
    std::vector<std::string> methods = {"GET", "HEAD", "OPTIONS", "POST", "PUT", "DELETE", "TRACE", "CONNECT"};

    for (std::string s : tempVec)
    {
        if (s != "" && s != "\t" && s != "\n" && s != " ")
            vec.push_back(s);
    }

    if (vec.size() < 3)
    {
        _status = "400";
        return;
    }
    for (std::string elem : vec)
    {
        if (elem.find(":") == std::string::npos)
        {
            for (std::string meth : methods)
            {
                if (elem.find(meth) != std::string::npos)
                {
                    _type = meth;
                    boost::split(interm, elem, boost::is_any_of(" "));
                }
                boost::split(interm, elem, boost::is_any_of(" "));
                if (interm.size() == 3 && interm[1] != "/favicon.ico")
                    _argument = interm[1];
            }
        }
        else
        {
            boost::split(interm, elem, boost::is_any_of(":"));
            if (interm.size() < 2)
            {
                _status = "400";
                return;
            }
            _headers[interm[0]] = interm[1];
            _fieldMap[interm[0]] = interm[1];
        }
    }
}

HttpRequest::HttpRequest()
{
}

HttpRequest::~HttpRequest()
{
}

void HttpRequest::setType(std::string type)
{
    _type = type;
}

std::string HttpRequest::getType(void) const
{
    return (_type);
}

void HttpRequest::setField(std::string key, std::string value)
{
    _fieldMap[key] = value;
}

void HttpRequest::setBody(std::string body)
{
    _resBody = body;
}

std::string HttpRequest::getArgument(void) const
{
    return (_argument);
}

std::string HttpRequest::getStatus(void) const
{
    return (_status);
}

std::string HttpRequest::generate(void)
{
    std::string result = "";

    result += _type;
    result += "\n";
    setField("Content-Length", std::to_string(_resBody.length()));

    for (auto it = _fieldMap.begin(); it != _fieldMap.end(); it++)
    {
        result += it->first;
        result += ": ";
        result += it->second;
        result += "\n";
    }
    result += "\n";
    result += _resBody;
    return (result);
}
