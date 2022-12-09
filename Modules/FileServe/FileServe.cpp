/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** FileServe
*/

#include "FileServe.hpp"

namespace Module {
    void FileServe::setService(void *service)
    {
        _service = (Service *)service;
    }

    void FileServe::close(void)
    {
    }

    void FileServe::run(void)
    {
    }

    int FileServe::init(std::string)
    {
        return (1);
    }

    std::string FileServe::getName(void)
    {
        return (_name);
    }

    int FileServe::getType(void)
    {
        return (_type);
    }

    void FileServe::launch(std::string trigger, HttpRequest &request, HttpRequest &response, std::string serviceRoot)
    {
        std::string arg = request.getArgument();
        int e = arg.find(".php");
        int f = arg.find(".html");

        if ((e != std::string::npos && e + 4 == arg.size()) || (f != std::string::npos && f + 5 == arg.size()))
            return;
        behavior("", request, response, serviceRoot);
    }

    void FileServe::behavior(std::string trigger, HttpRequest &request, HttpRequest &response, std::string serviceRoot)
    {
        std::string codeRoot = "../Modules/error/";
        void (FileServe::*ptr)(HttpRequest &, HttpRequest &, std::string);
        std::ifstream file("");
        std::vector<std::string> vec = {}, vec_field = {};
        std::string path = "", content = "", tmp = "", dir = "", cpy = "", ext = "", mime = "text/html; charset=UTF-8";

        if (request.getArgument() == "/")
        {
            std::ifstream _filePhp(serviceRoot + "index.html");
            std::ifstream _fileHtml(serviceRoot + "index.php");

            if (_filePhp.good() || _fileHtml.good())
                return;
            _filePhp.close();
            _fileHtml.close();
            path = serviceRoot;
        }
        else
        {
            boost::split(vec, request.getArgument(), boost::is_any_of("/"));
            if (vec.size() == 0)
                path = serviceRoot;
            else
            {
                path = serviceRoot;
                for (int i = 1; i < vec.size(); i++)
                {
                    path += vec[i];
                    if (i + 1 < vec.size())
                        path += "/";
                }
            }
        }

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

        if (!std::filesystem::exists(path.c_str()))
        {
            file.close();
            file.open(codeRoot + "404error.html");
            getline(file, content, '\0');
            response.setType("HTTP/1.1 " + code["404"]);
            response.setBody(content);
            file.close();
            return;
        }

        std::filesystem::perms p = std::filesystem::status(path).permissions();
        if ((p & std::filesystem::perms::owner_read) == std::filesystem::perms::none)
        {
            file.close();
            file.open(codeRoot + "403error.html");
            getline(file, content, '\0');
            response.setType("HTTP/1.1 " + code["403"]);
            response.setBody(content);
            return;
        }
        ptr = _functionMap[request.getType()];
        if (ptr)
            (this->*ptr)(request, response, serviceRoot);
        print(request.getType() + " " + request.getArgument() + "HTTP/1.1" + response.getType());
    }

    void FileServe::get(HttpRequest &request, HttpRequest &response, std::string serviceRoot)
    {
        std::vector<std::string> vec = {}, vec_field = {};
        std::string path = "", content = "", tmp = "", dir = "", cpy = "", ext = "", mime = "text/html; charset=UTF-8";

        if (request.getArgument() == "/") {
            std::ifstream _filePhp(serviceRoot + "index.html");
            std::ifstream _fileHtml(serviceRoot + "index.php");

            if (_filePhp.good() || _fileHtml.good())
                return;
            _filePhp.close();
            _fileHtml.close();
            path = serviceRoot;
        } else {
            boost::split(vec, request.getArgument(), boost::is_any_of("/"));
            if (vec.size() == 0)
                path = serviceRoot;
            else {
                path = serviceRoot;
                for (int i = 1; i < vec.size(); i++)
                {
                    path += vec[i];
                    if (i + 1 < vec.size())
                        path += "/";
                }
            }
        }
        if (std::filesystem::exists(path.c_str())) {
            switch (std::filesystem::status(path.c_str()).type()) {
                case std::filesystem::file_type::directory: {
                    dir = path;
                    dir.erase(0, serviceRoot.size());
                    if (dir == "")
                        dir = "/";
                    content += "<!DOCTYPE html><html><head><meta charset='utf-8'/><title>" + path + "</title></head><body>" + "<h1>Index of " + dir + "</h1>";
                    for (auto it = std::filesystem::directory_iterator(path.c_str()); it != std::filesystem::directory_iterator(); ++it)
                    {
                        tmp = (*it).path().string();
                        tmp.erase(0, serviceRoot.size());
                        cpy = tmp;
                        if (dir != "/")
                            cpy.erase(0, dir.size() + 1);

                        content += " <a href=\"" + tmp + "\">" + cpy;
                        content += "<br>";
                    }
                    content += "</body></html>";
                    break;
                } default: {
                    ext = std::filesystem::path(path.c_str()).extension().string();
                    std::ifstream _file(path, std::ios::binary);
                    size_t pos = _file.tellg();
                    size_t size = _file.tellg();

                    _file.seekg(0, std::ios::end);
                    _file.seekg(pos, std::ios::beg);
                    content.reserve(size);
                    content.append(
                        std::istreambuf_iterator<char>(_file),
                        std::istreambuf_iterator<char>());

                    _file.close();
                    if (_mimeTypes[ext] != "")
                        mime = _mimeTypes[ext];
                    break;
                }
            }
        } else
            return;
        response.setType("Http/1.1 200 OK");
        response.setField("Content-Type", mime);
        response.setBody(content);
    }

    void FileServe::head(HttpRequest &request, HttpRequest &response, std::string serviceRoot)
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

    void FileServe::options(HttpRequest &request, HttpRequest &response, std::string serviceRoot)
    {
        response.setType("HTTP/1.1 " + code["200"]);
        response.setField("allow", "OPTIONS, GET, HEAD, POST");
    }

    FileServe::FileServe()
    {
        _type = 2;
        _name = "FileServe";

        _mimeTypes[".aac"] = "audio/aac";
        _mimeTypes[".abw"] = "application/x-abiword";
        _mimeTypes[".arc"] = "application/octet-stream";
        _mimeTypes[".avi"] = "video/x-msvideo";
        _mimeTypes[".azw"] = "application/vnd.amazon.ebook";
        _mimeTypes[".bin"] = "application/octet-stream";
        _mimeTypes[".bmp"] = "image/bmp";
        _mimeTypes[".bz"] = "application/x-bzip";
        _mimeTypes[".bz2"] = "application/x-bzip2";
        _mimeTypes[".csh"] = "application/x-csh";
        _mimeTypes[".css"] = "text/css";
        _mimeTypes[".csv"] = "text/csv";
        _mimeTypes[".doc"] = "application/msword";
        _mimeTypes[".docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
        _mimeTypes[".eot"] = "application/vnd.ms-fontobject";
        _mimeTypes[".epub"] = "application/epub+zip";
        _mimeTypes[".gif"] = "image/gif";
        _mimeTypes[".htm"] = "text/html";
        _mimeTypes[".ico"] = "image/x-icon";
        _mimeTypes[".ics"] = "text/calendar";
        _mimeTypes[".jar"] = "application/java-archive";
        _mimeTypes[".jpeg"] = "image/jpeg";
        _mimeTypes[".jpg"] = "image/jpeg";
        _mimeTypes[".js"] = "application/javascript";
        _mimeTypes[".json"] = "application/json";
        _mimeTypes[".mid"] = "audio/midi";
        _mimeTypes[".midi"] = "audio/midi";
        _mimeTypes[".mpeg"] = "video/mpeg";
        _mimeTypes[".mpkg"] = "application/vnd.apple.installer+xml";
        _mimeTypes[".odp"] = "application/vnd.oasis.opendocument.presentation";
        _mimeTypes[".ods"] = "application/vnd.oasis.opendocument.spreadsheet";
        _mimeTypes[".odt"] = "application/vnd.oasis.opendocument.text";
        _mimeTypes[".oga"] = "audio/ogg";
        _mimeTypes[".ogv"] = "video/ogg";
        _mimeTypes[".ogx"] = "application/ogg";
        _mimeTypes[".otf"] = "font/otf";
        _mimeTypes[".png"] = "image/png";
        _mimeTypes[".pdf"] = "application/pdf";
        _mimeTypes[".ppt"] = "application/vnd.ms-powerpoint";
        _mimeTypes[".pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
        _mimeTypes[".rar"] = "application/x-rar-compressed";
        _mimeTypes[".rtf"] = "application/rtf";
        _mimeTypes[".sh"] = "application/x-sh";
        _mimeTypes[".svg"] = "image/svg+xml";
        _mimeTypes[".swg"] = "application/x-shockwave-flash";
        _mimeTypes[".swf"] = "application/x-shockwave-flash";
        _mimeTypes[".tar"] = "image/tiff";
        _mimeTypes[".tif"] = "image/tiff";
        _mimeTypes[".tiff"] = "image/tiff";
        _mimeTypes[".ts"] = "application/typescript";
        _mimeTypes[".ttf"] = "font/ttf";
        _mimeTypes[".vsd"] = "application/vnd.visio";
        _mimeTypes[".wav"] = "audio/x-wav";
        _mimeTypes[".weba"] = "audio/webm";
        _mimeTypes[".webm"] = "video/webm";
        _mimeTypes[".webp"] = "image/webp";
        _mimeTypes[".woff"] = "font/woff";
        _mimeTypes[".woff2"] = "font/woff2";
        _mimeTypes[".xhtml"] = "application/xhtml+xml";
        _mimeTypes[".xls"] = "application/vnd.ms-excel";
        _mimeTypes[".xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
        _mimeTypes[".xml"] = "application/xml";
        _mimeTypes[".xul"] = "application/vnd.mozilla.xul+xml";
        _mimeTypes[".zip"] = "application/zip";
        _mimeTypes[".3gp"] = "video/3gpp audio/3gpp";
        _mimeTypes[".3g2"] = "video/3gpp2";
        _mimeTypes[".7z"] = "application/x-7z-compressed";
        _mimeTypes["mpga"] = "audio/mpeg";
        _mimeTypes["mp2"] = "audio/mpeg";
        _mimeTypes["mp2a"] = "audio/mpeg";
        _mimeTypes["m2a"] = "audio/mpeg";
        _mimeTypes["m3a"] = "audio/mpeg";

        _functionMap["GET"] = &FileServe::get;
        _functionMap["HEAD"] = &FileServe::head;
        _functionMap["OPTIONS"] = &FileServe::options;
    }

    FileServe::~FileServe()
    {
    }

    void FileServe::print(std::string str)
    {
        if (!_service) {
            std::cout << "[" << _name << "]: " << str << std::endl;
            _service->writeLog("[" + _name + "]: " + str);
        }
        else
            _service->writeLog("[" + _service->getName() + " " + _name + "]: " + str);
    }

    boost::shared_ptr<FileServe> FileServe::create()
    {
        return boost::shared_ptr<FileServe>(
            new FileServe());
    }
}

BOOST_DLL_ALIAS(
    Module::FileServe::create,
    createModule)
