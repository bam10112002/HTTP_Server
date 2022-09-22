#include "../include/log.h"

Log* Log::Log_ = nullptr;

/**
 * @brief получение указателя на единственный экземпляр класса
 * 
 * @return Log* указатель на объект класса
 */
Log* Log::GetInstance()
{
    if ( Log_ == nullptr) 
    {
        Log_ = new Log();
    }
    return Log_;
}

/**
 * @brief Construct a new Log object
 * 
 */
Log::Log()
{
    logStream.open("log.txt", std::ios::app);
}

/**
 * @brief Destroy the Log object
 * 
 */
Log::~Log()
{
    logStream.close();
}

/**
 * @brief Делает запись строки в log file
 * 
 * @param req строка для логирования
 * @param type тип запроса (информационный, сообщение об ошибке)
 */
void Log::LogHTTPRequest(const std::string& req, LogType type)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    logStream << "time: " << dt << endl;

    logStream << "type: ";
    if (type == LogType::INFO)
        logStream << "INFO" << endl; 
    else if (type == LogType::UNKNOWNREQ)
        logStream << "Unknown request" << endl;

    logStream << "message: " << req << endl;
}