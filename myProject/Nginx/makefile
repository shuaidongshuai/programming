object= nginx.o keepAlive.o 
nginx: $(object)
	g++ -o nginx $(object)
keepAlive.o: common.h
nginx.o: Processpool.h

.PHONY:clean				#使用说明  make clean 
clean:					#	  就可以执下面语句
	rm -f *.o nginx client server1 server2 server3 server4 server5
