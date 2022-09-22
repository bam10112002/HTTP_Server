all : ./Client.cpp ./Server.cpp bin/serverLib.o bin/url.o  bin/http.o bin/log.o 
	@g++ Client.cpp bin/serverLib.o bin/http.o bin/url.o -o ./bin/client
	@g++ Server.cpp bin/serverLib.o bin/http.o bin/url.o bin/log.o -o ./bin/server
	@g++ main.cpp bin/http.o -o ./bin/main

bin/serverLib.o : src/server/include/server.h src/server/src/server.cpp src/server/src/sourse.h bin/http.o
	@g++ -c src/server/src/server.cpp bin/http.o -o bin/serverLib.o

bin/http.o : src/http/src/http.cpp src/http/include/http.h
	@g++ -c src/http/src/http.cpp -o bin/http.o

bin/url.o : src/url/include/url.h src/url/src/url.cpp bin/http.o
	@g++ -c src/url/src/url.cpp bin/http.o -o bin/url.o

bin/log.o : src/log/src/log.cpp src/log/include/log.h
	@g++ -c src/log/src/log.cpp -o bin/log.o

test: bin/http.o tests/httpTests.cpp
	@g++ tests/httpTests.cpp bin/http.o -o ./bin/httpTest.o
	@./bin/httpTest.o