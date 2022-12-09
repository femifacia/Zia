/*
** EPITECH PROJECT, 2022
** B-YEP-500-COT-5-1-zia-damia.tobossi
** File description:
** ConfigHandler
*/

#include "ConfigHandler.hpp"

ConfigHandler::ConfigHandler()
{
  _pathFile = "../zia.ini";
}

ConfigHandler::~ConfigHandler()
{
}

void ConfigHandler::setPathFile(std::string pathFile)
{
  _pathFile = pathFile;
}

int ConfigHandler::counterStr(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end, std::string elem)
{
  std::vector<std::string>::iterator ptr;
  int ct = 0;

  for (ptr = begin; ptr != end; ptr++)
  {
    if (*ptr == elem)
      ct++;
  }
  return (ct);
}

int ConfigHandler::counterInt(std::vector<int>::iterator begin, std::vector<int>::iterator end, int elem)
{
  std::vector<int>::iterator ptr;
  int ct = 0;

  for (ptr = begin; ptr != end; ptr++)
  {
    if (*ptr == elem)
      ct++;
  }
  return (ct);
}

std::vector<std::string> ConfigHandler::spliter(std::string str, std::string delim)
{
  std::vector<std::string> vec = {}, finalvec = {};

  boost::split(vec, str, boost::is_any_of(delim));
  for (std::string elem : vec)
  {
    if (elem != "")
      finalvec.push_back(elem);
  }
  return (finalvec);
}

bool ConfigHandler::isNumber(const std::string str)
{
  for (char c : str)
  {
    if (std::isdigit(c) == 0)
      return (false);
  }
  return (true);
}

std::string ConfigHandler::getValidContent(char const *filename)
{
  std::ifstream file(filename);
  std::string content = "", result = "";
  bool isMod = false, isServ = false;

  while (std::getline(file, content))
  {
    if (content.find("[Modules]") != std::string::npos)
      isMod = true;
    if (content.find("[Service]") != std::string::npos)
    {
      isServ = true;
      result += '\n';
    }
    result += content;
    result += ' ';
  }
  return ((isMod && isServ) ? result : "");
}

void ConfigHandler::getModulesInfo(std::string line, ConfigData *conf)
{
  std::vector<std::string> tempRes = {};
  MyModule mod = {};

  tempRes = spliter(line, " ");
  if (tempRes.size() < 2)
  {
    conf->isErr = true;
    return;
  }
  int size = tempRes.size();
  for (int i = 1; i < size; i++)
  {
    std::string k = tempRes[i];
    if (k.find("Path=") != std::string::npos)
      mod.path = spliter(k, "=")[1];
    else if (k.find("Module=") != std::string::npos)
      mod.modules.push_back(spliter(k, "=")[1]);
    else
    {
      conf->isErr = true;
      return;
    }
  }
  conf->mod = mod;
}

void ConfigHandler::getServicesInfo(std::string line, ConfigData *conf)
{
  std::vector<std::string> intermRes = {}, tempRes = {};

  tempRes = spliter(line, " ");
  if (tempRes.size() != 6)
  {
    conf->isErr = true;
    return;
  }
  ServiceData serv = {"", "", "", "", -1};
  int size = tempRes.size();
  for (int i = 1; i < size; i++)
  {
    std::string k = tempRes[i];
    intermRes = spliter(k, "=");
    if (intermRes.size() != 2)
    {
      conf->isErr = true;
      return;
    }
    if (k.find("Port=") != std::string::npos)
    {
      std::string s_port = intermRes[1];
      if (isNumber(s_port))
        serv.port = std::stoi(s_port);
      else
      {
        conf->isErr = true;
        return;
      }
    }
    else if (k.find("Root=") != std::string::npos)
      serv.root = intermRes[1];
    else if (k.find("Name=") != std::string::npos)
      serv.name = intermRes[1];
    else if (k.find("ModuleNetwork=") != std::string::npos)
      serv.networkModuleName = intermRes[1];
    else if (k.find("ModuleLogger=") != std::string::npos)
      serv.loggerModuleName = intermRes[1];
    else
    {
      conf->isErr = true;
      return;
    }
  }
  conf->services.push_back(serv);
}

ConfigData ConfigHandler::parser(char const *filename)
{
  std::string str = "";
  std::vector<std::string> lines = {}, tempRes = {}, intermRes = {};
  MyModule mod = {};
  std::vector<ServiceData> services = {};
  ConfigData conf = {false, {}, {}};

  if ((str = getValidContent(filename)) == "")
  {
    conf.isErr = true;
    return (conf);
  }
  lines = spliter(str, "\n");
  for (std::string str : lines)
  {
    if (str.find("[Modules]") != std::string::npos)
      getModulesInfo(str, &conf);
    else if (str.find("[Service]") != std::string::npos)
      getServicesInfo(str, &conf);
  }
  return (conf);
}

ConfigData ConfigHandler::getConfig(char const *filename)
{
  ConfigData conf = parser(filename);
  ConfigData finalConf = {false, {}, {}};
  std::vector<int> usedPort = {};

  if (conf.mod.path == "" || conf.mod.modules.empty())
  {
    finalConf.isErr = true;
    return (finalConf);
  }

  for (ServiceData serv : conf.services)
  {
    if (serv.name == "" || serv.networkModuleName == "" || serv.loggerModuleName == "" || serv.root == "" || serv.port == -1)
    {
      finalConf.isErr = true;
      return (finalConf);
    }
    if (counterStr(conf.mod.modules.begin(), conf.mod.modules.end(), serv.networkModuleName) != 1 
    || counterStr(conf.mod.modules.begin(), conf.mod.modules.end(), serv.loggerModuleName) != 1)
    {
      finalConf.isErr = true;
      return (finalConf);
    }
    usedPort.push_back(serv.port);
    if (counterInt(usedPort.begin(), usedPort.end(), serv.port) >= 2)
    {
      finalConf.isErr = true;
      return (finalConf);
    }
  }
  finalConf = conf;
  return (finalConf);
}

void ConfigHandler::update()
{
  std::ifstream fl(_pathFile.c_str());

  if (fl.good())
  {
    ConfigData conf = getConfig(_pathFile.c_str());

    if (conf.isErr == true)
    {
      std::cerr << "[ERROR] Error in configuration file" << std::endl;
      defaultUpdate();
      return;
    }
    _pathModule = conf.mod.path;
    _moduleArray = conf.mod.modules;
    _serviceArray.clear();
    for (ServiceData serv : conf.services)
    {
      _serviceArray.push_back(std::make_shared<Service>(serv.port, serv.name, serv.networkModuleName, serv.loggerModuleName, serv.root));
    }
  }
  else
  {
    std::cerr << "[ERROR] Configuration file doesn't exist" << std::endl;
    defaultUpdate();
  }
}

void ConfigHandler::defaultUpdate()
{
  _pathModule = "../Modules/lib/";
  _moduleArray = {"Http", "PhpCgi", "SSL"};
  _serviceArray = {std::make_shared<Service>(8000, "v1.zia", "Http", "Logger", "../Services/OVO/"), std::make_shared<Service>(9000, "v2.zia", "Http", "Logger", "../Services/Wa-Azo/")};
}

std::vector<std::shared_ptr<Service>> ConfigHandler::getServices() const
{
  return (_serviceArray);
}

std::string ConfigHandler::getModulePath() const
{
  return (_pathModule);
}

std::vector<std::string> ConfigHandler::getModules() const
{
  return (_moduleArray);
}

void ConfigHandler::printAll()
{
  printModulePath();
  printModules();
  printServices();
}

void ConfigHandler::printFilePath()
{
  std::cout << "The path of the configuration file is: " << _pathFile << std::endl;
}

void ConfigHandler::printModulePath()
{
  std::cout << "Module path is: " << _pathModule << std::endl;
}

void ConfigHandler::printModules()
{
  std::cout << "The available modules are: " << std::endl;
  for (std::string mod : _moduleArray)
  {
    std::cout << mod << std::endl;
  }
}

void ConfigHandler::printServices()
{
  std::cout << "The available services are:" << std::endl;
  for (std::shared_ptr<Service> serv : _serviceArray)
  {
    std::cout << "Service " << serv->getName() << " running on the port " << serv->getPort() << " with " << serv->getModuleNetwork() << " and accessible to " << serv->getPath() << std::endl;
    std::cout << "All login information are handled by " << serv->getModuleLogger() << " module." << std::endl;
  }
}