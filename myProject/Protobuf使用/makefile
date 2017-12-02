PROTO = proto

all: server client
server:
	g++ -std=c++11 -o server server.cc $(PROTO)/people.pb.cc $(PROTO)/test.pb.cc $(PROTO)/test2.pb.cc $(PROTO)/test3.pb.cc -lprotobuf
client:
	g++ -std=c++11 -o client client.cc $(PROTO)/people.pb.cc $(PROTO)/test.pb.cc $(PROTO)/test2.pb.cc $(PROTO)/test3.pb.cc -lprotobuf

.PHONY: clean
clean:
	rm client server
