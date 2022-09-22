#ifndef LOG_H
#define LOG_H
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>

using std::fstream;
using std::endl;

/**
 * @brief Класс логера, использующий паттерн singleton
 */
class Log
{
protected:
    Log();
    static Log* Log_;
    fstream logStream;

public:
    enum class LogType {INFO, UNKNOWNREQ};
    Log(Log& other) = delete;
    void operator=(const Log&) = delete;

    ~Log();
    static Log* GetInstance();
    void LogHTTPRequest(const std::string& req, LogType type);
};

#endif