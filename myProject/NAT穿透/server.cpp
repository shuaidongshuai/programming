#include <iostream>
#include "NATHoleSer.h"

int main(int argc, char *argv[]){
	if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " host port" << std::endl;
        return 1;
    }
	const char *ip = argv[1];
	int port = atoi(argv[2]);
	NATHoleSer(ip, port).Run();
	return 0;
}