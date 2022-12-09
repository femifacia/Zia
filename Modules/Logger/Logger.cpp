/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** Logger
*/

#include "Logger.hpp"

namespace Module {
    void Logger::setService(void *service)
    {
    }

    void Logger::close(void)
    {
    }

    void Logger::run(void)
    {
    }

    int Logger::init(std::string)
    {
        return (1);
    }

    std::string Logger::getName(void)
    {
        return (_name);
    }

    int Logger::getType(void)
    {
        return (_type);
    }


    Logger::Logger()
    {
        _name = "Logger";
        _type = 3;

        setPath("../log.txt");
    }

    Logger::~Logger()
    {
    }

    void Logger::launch(std::string trigger, HttpRequest &request, HttpRequest &response, std::string serviceRoot)
    {
    }

    void Logger::behavior(std::string trigger, HttpRequest &request, HttpRequest &response, std::string serviceRoot)
    {
    }

    std::string Logger::getPath() const
    {
        return (_path);
    }

    void Logger::setPath(std::string path)
    {
        _path = path;
    }

    std::mutex *Logger::getMutex()
    {
        return (&_mutex);
    }

    void Logger::write(std::string text)
    {
        std::string content = "";
        std::ifstream file(getPath());
        std::ofstream stream(getPath(), std::ios_base::app);
        std::mutex *mutex = getMutex();
        boost::posix_time::ptime timeLocal = boost::posix_time::second_clock::local_time();
        auto curdate = timeLocal.date();
        auto curtime = timeLocal.time_of_day();

        std::getline(file, content, '\0');
        mutex->lock();
        if (content[content.size() - 1] != '\n' && content != "") {
            file.close();
            stream << "\n";
        }
        content = "[";
        content += (std::to_string(curdate.year()) + "-" + std::to_string(curdate.month()) + "-" + std::to_string(curdate.day()) + " ");
        content += (std::to_string(curtime.hours()) + ":" + std::to_string(curtime.minutes()) + ":" + std::to_string(curtime.seconds()));
        content += "] ";
        content += text;
        stream << content << "\n";
        stream.close();
        mutex->unlock();
    }

    void Logger::print(std::string str)
    {
    }

    std::ofstream& operator<<(Logger &logger, std::string content)
    {
        std::mutex *mutex = logger.getMutex();
        boost::posix_time::ptime timeLocal = boost::posix_time::second_clock::local_time();
        auto curdate = timeLocal.date();
        auto curtime = timeLocal.time_of_day();
        std::string line = "";

        line += "[";
        line += (std::to_string(curdate.year()) + "-" + std::to_string(curdate.month()) + "-" + std::to_string(curdate.day()) + " ");
        line += (std::to_string(curtime.hours()) + ":" + std::to_string(curtime.minutes()) + ":" + std::to_string(curtime.seconds()));
        line += "] ";
        mutex->lock();
        boost::shared_ptr<std::ofstream> out = boost::shared_ptr<std::ofstream>(new std::ofstream);
        out->open(logger.getPath(), std::ios_base::app);
        *out << line;
        *out << content;
        if (content[content.size()-1] != '\n')
            *out << "\n";
        out->close();
        mutex->unlock();
        return (*out);
    }

    boost::shared_ptr<Logger> Logger::create() {
        return boost::shared_ptr<Logger>(
            new Logger()
            );
    }
}

BOOST_DLL_ALIAS(
    Module::Logger::create,
    createModule
)