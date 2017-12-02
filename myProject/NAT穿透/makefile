LIB = lib
all: server client

server: server.o
	g++ -std=c++11 -o server $(LIB)/server.o
%.o: %.cpp
	g++ -std=c++11 -c $< -o $(LIB)/$@

client: client.o
	g++ -std=c++11 -o client $(LIB)/client.o -pthread
%.o: %.cpp
	g++ -std=c++11 -c $< -o $(LIB)/$@ 

.PHONY: clean
clean:
	-rm -rf $(LIB)/* server client