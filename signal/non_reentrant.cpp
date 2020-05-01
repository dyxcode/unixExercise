#include <cstddef>
#include <cstdlib>
#include <unistd.h>
#include <pwd.h>
#include <signal.h>
#include <string.h>
#include <iostream>
using namespace std;

void my_alarm(int signo) {
	struct passwd *rootptr;

	cout << "in signal handler" << endl;
	if ((rootptr = getpwnam("root")) == NULL) {
		cerr << "getpwnam(root) error" << endl;
		exit(1);
	}
	alarm(1);
}

int main(void) {
	struct passwd *ptr;

	signal(SIGALRM, my_alarm);
	alarm(1);
	
	while (1) {
		if ((ptr = getpwnam("dyx")) == NULL) {
			cerr << "getpwnam error" << endl;
			exit(1);
		}
		if (strcmp(ptr->pw_name, "dyx") != 0)
			cerr << "return value corrupted, pw_name = " << ptr->pw_name << endl;
	}


	return 0;
}
