#include <unistd.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void printstr(const char *str) {
	cout << unitbuf;
	for (size_t i = 0; str[i] != 0; ++i) {
		cout << str[i];
	}
}

int main(void) {
	pid_t pid;

	if ((pid = fork()) < 0) {
		cerr << "fork error" << endl;
		exit(1);
	} else if (pid == 0) {
		printstr("output from child\n");
	} else {
		printstr("output from parent\n");
	}

	return 0;
}
