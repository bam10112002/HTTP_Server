## О проекте
Проект представяет собой вэб серевер, предназначенный для обработки HTTP запросов от браузера.
В свою очередь сервер отправляет клиенту ответ в виде HTML страцицы, картинки или любого иного файла, 
который запросит браузер.


## Как использовать
Для компиляции проекта используется makefile, запуск которого осуществляется вызовом ***make***. 
После компиляции необходимо запустить сервер вызовом ***./bin/server PORT***, 
где вместо PORT подставляется любой незанятый порт на котором будет запущен сервер.  
Подключаене к серверу осуществляется по порту на котором был запущен сервер. ПО поддерживает url адресацию, 
в случае если зпрашиваемый url не поддерживается, та браузеру будет возвращена страница ***404 page not found***. 
