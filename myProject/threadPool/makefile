VPATH = src
all: client server

client: client.o
	g++ -std=c++11 -o client client.o -pthread
*.o: *.cpp
	g++ -std=c++11 -c $< -o $@

server: server.o
	g++ -std=c++11 -o server server.o -pthread
*.o: *.cpp
	g++ -std=c++11 -c $< -o $@
	
.PHONY: clean
clean:
	-rm -rf server client erver.o client.o