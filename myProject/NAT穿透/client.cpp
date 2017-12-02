#include <iostream>
#include "NATHoleCli.h"

int main(int argc, char *argv[]){
	if (argc != 3) {
		std::cout << "Usage: %s host port" << argv[0] << std::endl;
		return 1;
	}
	const char *ip = argv[1];
	int port = atoi(argv[2]);
	NATHoleCli(ip, port).Run();
	return 0;
}