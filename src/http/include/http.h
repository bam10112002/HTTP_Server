#ifndef HTTP_H
#define HTTP_H

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include "../../json/single_include/nlohmann/json.hpp"

using std::string;
using nlohmann::json;

/**
 * @brief Базовый HTTP класс  
 */
class HTTP
{
protected:
    void skipWhitespace(const string&, int& ind) const;
    void LoadFile(const string& path, string& text) const;
};


/**
 * @brief Класс отвечающий за http запросы к серверу
 */
class HTTPRequest : public HTTP
{
public:
    enum class RequestType {FILE, URL};

private:
    string method, protocol;
    std::vector<string> path;
    RequestType reqType;

    void ParseFirstLine(const string&);
    std::vector<string> ParsePath(const std::string&) const;
    RequestType checkReqType(const std::vector<string>& path) const;

public:
    void ParseHttp(const string&);
    
    // Get
    string Method() const;
    RequestType ReqType() const;
    std::vector<string> Path() const;
    string Protocol() const;
};


/**
 * @brief Класс отвечает за ответ от сервера к клиенту
 */
class HTTPResponse : public HTTP
{
private:
    string firstLine;
    std::string body;

public:
    void Load(string path);
    void makeRespnse(int code, string status, string bodyLoad);
    void make404();
    string getResponse();
};

#endif

