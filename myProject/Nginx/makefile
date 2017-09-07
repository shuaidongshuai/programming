all:nginx client server1 server2 server3 server4 server5

nginx:Nginx.o keepAlive.o
	g++ -o $@ $^
Nginx.o:Nginx.cpp
	g++ -g -c  Nginx.cpp
#ShaData.o:ShaData.cpp
#	g++ -g -c  ShaData.cpp
#epollTask.o:epollTask.cpp
#	g++ -g -c epollTask.cpp

client:client.o 
	g++ -o $@ $^
server1:server1.o keepAlive.o
	g++ -o $@ $^
server2:server2.o keepAlive.o
	g++ -o $@ $^
server3:server3.o keepAlive.o
	g++ -o $@ $^
server4:server4.o keepAlive.o
	g++ -o $@ $^
server5:server5.o keepAlive.o
	g++ -o $@ $^

server1.o:server1.cpp
	g++ -g -c server1.cpp

.PHONY:clean				#使用说明  make clean 
clean:					#	  就可以执行下面语句
	rm -f *.o nginx client server1 server2 server3 server4 server5
