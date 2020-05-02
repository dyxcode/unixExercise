#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
using namespace std;

sigjmp_buf jmpbuf;
volatile sig_atomic_t canjump;

void pr_mask(const char *str) {
	sigset_t sigset;
	int errno_save;

	errno_save = errno;
	if (sigprocmask(0, NULL, &sigset) < 0) {
		cerr << "sigprocmask error" << endl;
		return ;
	} else {
		cout << str;
		if (sigismember(&sigset, SIGINT))
			cout << " SIGINT";
		if (sigismember(&sigset, SIGQUIT))
			cout << " SIGQUIT";
		if (sigismember(&sigset, SIGUSR1))
			cout << " SIGUSR1";
		if (sigismember(&sigset, SIGALRM))
			cout << " SIGALRM";
		
		cout << endl;
	}
	errno = errno_save;
}

void sig_usr1(int signo) {
	time_t starttime;

	if (canjump == 0)
		return;			// unexpected signal, ignore
	pr_mask("starting sig_usr1: ");

	alarm(3);
	starttime = time(NULL);
	while (1) {			// busy wait for 5 seconds
		if (time(NULL) > starttime + 5)
			break;
	}
	
	pr_mask("finishing sig_usr1: ");

	canjump = 0;
	siglongjmp(jmpbuf, 1);
}

void sig_alrm(int signo) {
	pr_mask("in sig_alrm: ");
}

int main(void) {
	if (signal(SIGUSR1, sig_usr1) == SIG_ERR)
		cerr << "signal(SIGUSR1) error" << endl;
	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		cerr << "signal(SIGALRM) error" << endl;

	pr_mask("starting main: ");

	if (sigsetjmp(jmpbuf, 1)) {
		pr_mask("ending main: ");
		exit(0);
	}
	canjump = 1;			// now sigsetjmp() is OK

	while(1)
		pause();

	return 0;
}
