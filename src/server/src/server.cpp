#include "../include/server.h"

/**
 * @brief отправка сообщения через сокет
 * 
 * @param msg данные, в формате строки для отправки
 */
void Net::Send(const std::string & msg) const
{   
    if(sock < 0)
        perror("socket:");

    if (send(sock, msg.c_str(), sizeof(char)*msg.size(), 0) == -1)
    {
        perror("send:");
        close(sock);
    }
}

/**
 * @brief прием сообщения через сокет
 * 
 * @param msg данные, в формате строки, в которые будут считаны данные
 */
void Net::Recv(std::string & msg) const
{
    int bytes_read;
    char buf[BUFSIZE+1];

    while(1)
    {
        bytes_read = recv(sock, buf, BUFSIZE, 0);
        buf[bytes_read] = 0;

        msg += std::string(buf);
        if(bytes_read <= BUFSIZE) 
            break;
    }
}

/**
 * @brief Закрытие сокета
 */
void Net::Shutdown()
{
    shutdown(sock,2);
    sock = -1;
}
void Net::Close()
{
    close(sock);
}

/**
 * @brief конфигурирует структуру sock addr in
 * 
 * @param port порт для отправки или приема сообщений
 * @param ip ip адрес для отправки или приема сообщений
 * @return sockaddr_in структура настройки сокета
 */
sockaddr_in Net::getAddr(int port, const std::string& ip) const
{
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    
    return addr;
}

NetServer::NetServer(int port, const std::string& ip)
{
    addr = getAddr(port, ip);

    if((listener = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        exit(1);
    }

    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(1);
    }
    
    listen(listener, 1);
}
void NetServer::Accept()
{
    sock = accept(listener, nullptr, nullptr);
    if(sock < 0)
    {
        perror("accept");
    }
}

NetClient::NetClient()
{
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }
}
void NetClient::Connect(int port, const std::string& ip)
{

    addr = getAddr(port, ip);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
    }
}
