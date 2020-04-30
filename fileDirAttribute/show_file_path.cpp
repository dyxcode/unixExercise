#include <cstdlib>
#include <unistd.h>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cerr << "usage : ./a.out path" << endl;
		exit(1);
	}

	char buf[96];
	if (chdir(argv[1]) < 0) {
		cerr << "chdir error" << endl;
		exit(1);
	}
	if (getcwd(buf, 96) == NULL) {
		cerr << "getcwd error" << endl;
		exit(1);
	}
	cout << "path = " << buf << endl;

	return 0;
}
