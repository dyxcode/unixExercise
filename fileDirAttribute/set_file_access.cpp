#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cerr << "usage: ./a.out file_path" << endl;
		exit(1);
	}
	struct stat buf;
	if (stat(argv[1], &buf) < 0) {
		cerr << "stat error" << endl;
		exit(1);
	}
	if (chmod(argv[1], 0777) < 0) {
		cerr << "chmod error" << endl;
		exit(1);
	}

	return 0;
}
