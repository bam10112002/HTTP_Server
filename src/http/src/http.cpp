#include "../include/http.h"

//! HTTP
/**
 * 
 * @brief Пропуск пробельных символов в заднной строке
 * 
 * @param str строка в которой пропускаются пробелы
 * @param ind индекс с которого осуществляется пропуск
 */
void HTTP::skipWhitespace(const string& str, int& ind) const
{
    while (str[ind] == ' ')
        ind++;
}

/**
 * @brief Чтение даных из файла в строку
 * 
 * @param path путь до файла
 * @param text ссылка на строку, в которую происходит считывание
 */
void HTTP::LoadFile(const string& path, string& text) const
{
    std::fstream fs(path);
    if (!fs)
        std::cout << "ERROR OPEN FILE" << std::endl;
    while (!fs.eof())
    {
        text += fs.get();
    }
    text.pop_back();
}

//! HTTP Request
/**
 * @brief Парсинг HTTP зароса
 * 
 * @param request текстовый вид HTTP запроса
 */
void HTTPRequest::ParseHttp(const string& request)
{
    int endFirstLine = request.find("\n");
    if (endFirstLine == std::string::npos)
    {
        std::cout << "ERROR undefined /n in func <<HTTPRequest::ParseHttp>>" << std::endl << request << std::endl << std::endl;
        return;
    }
    string firstLine = request.substr(0, endFirstLine);
    ParseFirstLine(firstLine);
}

/**
 * @brief Парсинг первой строки запроса
 * 
 * @param firstLine Первая строка запроса с протоколом и тп.
 */
void HTTPRequest::ParseFirstLine(const string& firstLine)
{
    int ind = 0, oldind = 0;

    skipWhitespace(firstLine, ind);
    oldind = ind;
    while (ind <= firstLine.size())
    {
        if (firstLine[ind] == ' ')
            break;
        ++ind;
    }
    method = firstLine.substr(oldind, ind-oldind);
    skipWhitespace(firstLine, ind);
    oldind = ind;

    while (ind <= firstLine.size())
    {
        if (firstLine[ind] == ' ')
            break;
        ++ind;
    }
    string pathString = firstLine.substr(oldind, ind-oldind);
    path = ParsePath(pathString);
    reqType = checkReqType(path);
    skipWhitespace(firstLine, ind);
    oldind = ind;

    while (ind <= firstLine.size())
    {
        if (firstLine[ind] == ' ' || firstLine[ind] == '\n')
            break;
        ++ind;
    }
    protocol = firstLine.substr(oldind, ind-oldind);

}

/**
 * @brief Парсиенг url запроса и его представление в виде вектора с разделителем "/"
 * 
 * @param path url в строковом формате
 * @return std::vector<string> путь в виде вктора
 */
std::vector<string> HTTPRequest::ParsePath(const std::string& path) const
{
    int firstInd = 0, secondInd = 0;
    std::vector<string> vec;

    while(1)
    {
        secondInd = path.find("/", firstInd+1);
        if (secondInd == std::string::npos)
            break;
        vec.push_back(path.substr(firstInd, secondInd - firstInd));
        firstInd = secondInd;
    }
    vec.push_back(path.substr(firstInd));
    return vec;
}

/**
 * @brief Определение вида запроса (файл или url)
 * 
 * @param path url запрос
 * @return HTTPRequest::RequestType тип запроса 
 */
HTTPRequest::RequestType HTTPRequest::checkReqType(const std::vector<string>& path) const
{
    std::string last = path[path.size() -1];
    std::fstream confFS("./configurate/config.json", std::ios::in);
    json conf = {};
    confFS >> conf;
    for (const auto& dir : conf["templates"])
    {
        std::ifstream FS(dir.get<string>() + last);
        if (FS && last != "/")
        {
            FS.close();
            return RequestType::FILE;
        }
    }
    return RequestType::URL;
}

string HTTPRequest::Method()                         const { return method;  }
string HTTPRequest::Protocol()                       const { return protocol;}
std::vector<string> HTTPRequest::Path()              const { return path;    }
HTTPRequest::RequestType HTTPRequest::ReqType()      const { return reqType; }
        
//! HTTP Response
/**
 * @brief Создает ответное HTTP сообщение
 * 
 * @param code код ответа (200, 404 и тд)
 * @param status расшифровка кода (OK, Not found и др)
 * @param bodyLoad путь до файла, который нужно загрузить
 */
void HTTPResponse::makeResponse(int code, string status, string bodyLoad)
{
    firstLine = "HTTP/1.1 " + std::to_string(code) + " " + status;
    if (bodyLoad != "")
        Load(bodyLoad);
}

/**
 * @brief Создание ответной строницы 404
 */
void HTTPResponse::make404()
{
    firstLine = "HTTP/1.1 404 Not found";
    Load("/404.html");
}

/**
 * @brief возвращает ответное сообщение в виде строки
 * 
 * @return string HTTP ответ клиенту в строковом формате
 */
string HTTPResponse::getResponse()
{
    string header = "Content-Length: " + std::to_string(body.size());
    return (firstLine + "\n" + header + "\n\n" + body);
}

/**
 * @brief Считывание файла в body
 * 
 * @param path путь до загружаемого файла
 */
void HTTPResponse::Load(string path)
{
    std::fstream fs;
    std::string fullPath;  
    json conf = {};
    std::fstream confFS("./configurate/config.json", std::ios::in);
    confFS >> conf;
    for (const auto& dir : conf["templates"])
    {
        fullPath = dir.get<string>() + path;
        fs.open(fullPath);
        if (!fs)
        {
            std::cout << "FILE NOT FOUND: " << fullPath << std::endl;
            body = "";
            firstLine = "HTTP/1.1 404 Page not found";
        }
        else 
        {
            LoadFile(fullPath, body);
            firstLine = "HTTP/1.1 200 OK";
        }
        fs.close();
    }
}
