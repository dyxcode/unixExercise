#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char *argv[]) {
	struct stat buf;
	
	for (int i = 1; i < argc; ++i) {
		cout << argv[i] << ": ";
		if (lstat(argv[i], &buf) < 0) {
			cerr << "lstat error" << endl;
			continue;
		}
		if (S_ISREG(buf.st_mode))
			cout << "regular" << endl;
		else if (S_ISDIR(buf.st_mode))
			cout << "directory" << endl;
		else if (S_ISCHR(buf.st_mode))
			cout << "character special" << endl;
		else if (S_ISBLK(buf.st_mode))
			cout << "block special" << endl;
		else if (S_ISFIFO(buf.st_mode))
			cout << "fifo" << endl;
		else if (S_ISLNK(buf.st_mode))
			cout << "symbolic link" << endl;
		else if (S_ISSOCK(buf.st_mode))
			cout << "socket" << endl;
		else
			cout << "unknown mode" << endl;
	}

	return 0;
}
