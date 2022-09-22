#include "../include/url.h"

/**
 * @brief метод для установки следующего обработчика в цепочке ответственности
 * 
 * @param handler указатель на следущий обработчик
 * @param handlerName имя обработчика, которе будет фигурировать в url запросе
 */
void Handler::SetNext (Handler *handler, std::string handlerName)
{
    next.push_back(std::make_pair(handler, handlerName));
}

Url::Url()
{
    mainHandler.SetNext(&progectHandler, "/progect");
    mainHandler.SetNext(&libraryHandler, "/library");
}

/**
 * @brief Обработка url запроса
 * 
 * @param path url запрос
 * @param http возвращает HTTP ответ клиенту (страница или сообщение об ошибке)
 * @return true страница найдена
 * @return false страница не найдена (page not found)
 */
bool Library::Handle(std::vector<std::string> path, HTTPResponse& http)
{
    for (const auto& handler : next)
    {
        if (handler.second == path.at(0))
        {
            path.erase(path.cbegin());
            return handler.first->Handle(path, http);
        }
    }
    if(path.size() != 1)
    {
        http.make404();
        return false;
    }
        

    // пользовательская часть
    if (path[0] == "/cost")
    {
        http.makeRespnse(200,"OK", "/library.html");
        return true;
    }
    else
    {
        http.make404();
        return false;
    }
}
bool Progect::Handle(std::vector<std::string> path, HTTPResponse& http)
{
    for (const auto& handler : next)
        if (handler.second == path.at(0))
        {
            path.erase(path.cbegin());
            return handler.first->Handle(path, http);
        }

    if(path.size() != 1)
    {
        http.make404();
        return false;
    }
        

    // пользовательская часть
    if (path[0] == "/cost")
    {
        http.makeRespnse(200,"OK", "/template.html");
        return true;
    }
    else
    {
        http.make404();
        return false;
    }
}
bool Main::Handle(std::vector<std::string> path, HTTPResponse& http)
{
    for (const auto& handler : next)
    {
        if (handler.second == path.at(0))
        {
            path.erase(path.cbegin());
            return handler.first->Handle(path, http);
        }
    }
    if(path.size() != 1)
    {
        http.make404();
        return false;
    }
        

    // пользовательская часть
    if (path[0] == std::string("/"))
    {
        http.makeRespnse(200, "OK", "/index.html");
        return true;
    }
    else
    {
        http.make404();
        return false;
    }
}
