#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include <iostream>
#include <string>
using std::cerr;
using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cerr << "usage: a.out fd" << endl;
		exit(1);
	}
	
	int val;
	if ((val = fcntl(std::stoi(argv[1]), F_GETFL, 0)) < 0) {
		cerr << "fcntl error for fd " << std::stoi(argv[1]) << endl;
		exit(1);
	}

	switch (val & O_ACCMODE) {
		case O_RDONLY : cout << "read only"; break;
		case O_WRONLY : cout << "write only"; break;
		case O_RDWR : cout << "read write"; break;
		default : 
			cerr << "unknown access mode" << endl;
			exit(1);
	}

	if (val & O_APPEND)
		cout << ", append";
	if (val & O_NONBLOCK)
		cout << ", nonblocking";
	if (val & O_SYNC)
		cout << ", synchronous writes";
	cout << endl;

	return 0;
}
