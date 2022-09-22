#include <iostream>
#include <string>
#include <vector>
using std::string;
#include "./src/http/include/http.h"

/*
 * код говно Handle должен принемать ссылку на страницу, котрую будет возвращать
 * переименовать Handle (хуй знает на что)
 * 
 * По таскам 
 * 1) Дописать url обработчик
 * 2) Loger
 * 3) Доотправка сss автоматизированно
 *  3.1) парсинг Accept: text/html or text/css  СДЕЛАНО
 *  3.2) обрезать путь до css: убрать начальный /
 *  3.3) поиск запрашиваемого файла в директории с шаблоном
 * 4) конфигурационный файл с указанием путей до файлов с данными: css + html
 */


// Interfase
class Handler
{
protected:
    std::vector<std::pair<Handler*, std::string>> next;
    std::pair<string,string> Parse(string request)
    {
        int n = request.find("/", 1);
        if (n == std::string::npos)
        {
            // конечная страница редиректа не ожидается
            return std::make_pair(request, request);
        }

        // конфигурируем: nextUrl следующий обработчик, nextReq запрос след. обработчику
        std::string nextUrl = request.substr(0,n);
        std::string nextReq = request.substr(n);

        return std::make_pair(nextUrl, nextReq);
    }

public:
    virtual void SetNext (Handler *handler, std::string handlerName)
    {
        next.push_back(std::make_pair(handler, handlerName));
    }
    virtual std::string Handle(std::string request) = 0;
};

// кастомные классы обработки
class Main : public Handler
{
public:
    std::string Handle(std::string request) override
    {
        std::pair<string, string> path = Parse(request);

        for (const auto& handler : next)
        {
            if (handler.second == path.first)
            {
                return handler.first->Handle(path.second);
            }
        } 
        //TODO: return 404;
        return "404 main";
    }
};

class Progect : public Handler
{
public:
    std::string Handle(std::string request) override
    {
        std::pair<string, string> path = Parse(request);

        for (const auto& handler : next)
        {
            if (handler.second == path.first)
            {
                return handler.first->Handle(path.second);
            }
        }

        //TODO: return 404;
        return "404 progect";

    }
};

class Library : public Handler
{
public:
    std::string Handle(std::string request) override
    {
        std::pair<string, string> path = Parse(request);

        for (const auto& handler : next)
        {
            if (handler.second == path.first)
            {
                return handler.first->Handle(path.second);
            }
        }
        if (path.second == "/about")
            return "about lib";
        else if (path.second == "/cost")
            return "cost lib";
        else 
        {
            //TODO: return 404;
            return "404 library";
        }
    }
};

class Boost : public Handler
{
public:
    std::string Handle(std::string request) override
    {
        // Тут стоит как-то вынести в отдельную сущнсть
        // проблема - двойной return или страница или путь до страницы которую конфигурирует пользователь

        std::pair<string, string> path = Parse(request);
        for (const auto& handler : next)
        {
            if (handler.second == path.first)
            {
                return handler.first->Handle(path.second);
            }
        }

        if (path.second == "/about")
            return "about boost";
        else if (path.second == "/author")
            return "author boost";
        else 
        {
            //TODO: Сконфигурированная 404;
            return "404 boost";
        }
    }
};



int main(int argc, char const *argv[])
{
    

    return 0;
}
