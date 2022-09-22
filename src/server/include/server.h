#ifndef SERVER_H
#define SERVER_H
#include "../src/sourse.h"

/**
 * @brief базовый класс для серерного и клиентского класса
 */
class Net
{
protected:
    const int BUFSIZE = 2048;
    int sock;
    struct sockaddr_in addr;

    sockaddr_in getAddr(int port, const std::string& ip) const;

public:
    virtual ~Net(){}
    void Send(const std::string &) const;
    void Recv(std::string &) const;
    void Shutdown();
    void Close();
};

/**
 * @brief Класс вэб сервера инкапсулирующий взаимодействие с сокетами, работающий на linux
 */
class NetServer : public Net
{
private:
    int listener;

public:
    NetServer(int port,  const std::string& ip);
    void Accept();
};

/**
 * @brief Класс вэб клиента инкапсулирующий взаимодействие с сокетами, работающий на linux
 * 
 */
class NetClient : public Net
{
private:
    struct sockaddr_in addr;

public:
    NetClient();
    void Connect(int port, const std::string& ip);
};

#endif
