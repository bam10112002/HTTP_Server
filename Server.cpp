#include "./src/server/include/server.h"
#include "./src/http/include/http.h"
#include "./src/url/include/url.h"
#include "./src/log/include/log.h"

int main(int argc, char** argv)
{
    std::cout << "============>> SERVER STARTED <<============" << std::endl;
    NetServer server(std::stoi(string(argv[1])), "0.0.0.0");
    Url url;
    Log* log = Log::GetInstance();
    
    while(1)
    {
        HTTPRequest req;
        HTTPResponse res;
        std::string msg;

        server.Accept();
        server.Recv(msg);

        if (msg == string("close"))
            return 0;
        if (msg == "")
            continue;

        req.ParseHttp(msg);
        std::cout << "path:" ;
        for (const auto & obj : req.Path())
        {
            std::cout << " " << obj;
        }

        if (req.ReqType() == HTTPRequest::RequestType::FILE)
            res.Load(req.Path()[req.Path().size()-1]);
        else if (req.ReqType() == HTTPRequest::RequestType::URL)
            url.mainHandler.Handle(req.Path(), res);

        log->LogHTTPRequest(msg, Log::LogType::INFO);

        server.Send(res.getResponse());
        server.Close();
        // std::cout << "\033[31m END CONECTION \033[0m" << std::endl;
    
    }
   
    return 0;
}