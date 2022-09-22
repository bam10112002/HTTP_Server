#include <iostream>
#include <string>
#include <vector>
#include "../../http/include/http.h"
using std::string;

/**
 * @brief Класс интерфейс для обработчиков запросов, построенный по паттерну цепочка ответственностей
 * для работы класса нужно реализовать метод Handle для класса наследника,
 * после чего зарегистрировать его в конструкторе класса URL
 */
class Handler
{
protected:
    std::vector<std::pair<Handler*, std::string>> next;

public:
    virtual void SetNext (Handler *handler, std::string handlerName);
    virtual bool Handle(std::vector<std::string> path, HTTPResponse& http) = 0;
};

// кастомные классы обработки
class Main : public Handler
{
public:
    bool Handle(std::vector<std::string> path, HTTPResponse& http) override;

};

class Progect : public Handler
{
public:
    bool Handle(std::vector<std::string> path, HTTPResponse& http) override;

};

class Library : public Handler
{
public:
    bool Handle(std::vector<std::string> path, HTTPResponse& http) override;

};

/**
 * @brief класс отвечающий за инкапсуляцию обработчика запросов, построенный на паттерне цепочка ответственностей
 */
class Url
{
public:
    Url();
    Main mainHandler;
    Progect progectHandler;
    Library libraryHandler;
};
