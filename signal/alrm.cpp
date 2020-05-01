#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>
#include <setjmp.h>
using namespace std;

jmp_buf env_alrm;

void sig_alrm(int signo) {
	longjmp(env_alrm, 1);
}

int main(void) {
	int n;
	char line[128];

	if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
		cerr << "signal(SIGALRM) error" << endl;
		exit(1);
	}

	if (setjmp(env_alrm) != 0) {
		cout << "read timeout" << endl;
		exit(0);
	}

	alarm(5);
	if ((n = read(STDIN_FILENO, line, 128)) < 0) {
		cerr << "read error" << endl;
		exit(1);
	}
	alarm(0);
	write(STDOUT_FILENO, line, n);

	return 0;
}
