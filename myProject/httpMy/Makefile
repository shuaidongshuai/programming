object = http_conn.o myHttp.o
myHttp: $(object)
	g++ -o myHttp $(object) -pthread
.PHONY: clean
clean:
	-rm myHttp $(object)
