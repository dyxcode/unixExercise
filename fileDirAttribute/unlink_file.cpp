#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cerr << "usage : ./a.out filename" << endl;
		exit(1);
	}

	if (open(argv[1], O_RDWR) < 0) {
		cerr << "open error" << endl;
		exit(1);
	}
	if (unlink(argv[1]) < 0) {
		cerr << "unlink error" << endl;
		exit(1);
	}
	cout << "file unlinked" << endl;
	sleep(15);
	cout << "done" << endl;

	return 0;
}
