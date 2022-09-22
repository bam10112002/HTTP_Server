#include "./src/server/include/server.h"


char message[] = "Hello there!\n";
char buf[sizeof(message)];

int main()
{
    NetClient client;
    client.Connect(2010, "0.0.0.0");

    std::string msg = "close";
    
    client.Send(msg);
    client.Close();
    
    return 0;
}