#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
using namespace std;

int globvar = 6;
const char buf[] = "a write to stdout\n";

int main(void) {
	int var;
	pid_t pid;
	
	var = 88;
	if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf) - 1) {
		cerr << "write error" << endl;
		exit(1);
	}
	cout << "before fork" << endl;

	if ((pid = fork()) < 0) {
		cerr << "fork error" << endl;
		exit(1);
	} else if (pid == 0) {
		globvar++;
		var++;
	} else {
		sleep(2);
	}

	cout << "pid = " << getpid() << "glob = " << globvar << "var = " << var << endl;
	return 0;
}
