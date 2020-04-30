#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;

int main(void) {
	pid_t pid;

	cout << "parent pid = " << getpid() << endl;

	if ((pid = fork()) < 0) {
		cerr << "fork error" << endl;
		exit(1);
	}
	else if (pid == 0) {
		if ((pid = fork()) < 0) {
			cerr << "fork error" << endl;
			exit(1);
		}
		else if (pid > 0) {
			cout << "first child, pid = " << getpid() << endl;
			exit(0);
		}

		sleep(2);
		cout << "second child, parent pid = " << getppid() << endl;
		exit(0);
	}

	if (waitpid(pid, NULL, 0) != pid) {
		cerr << "waitpid error" << endl;
		exit(1);
	}


	return 0;
}
