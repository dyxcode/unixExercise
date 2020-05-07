#include <csignal>
#include <unistd.h>
#include <errno.h>
#include <iostream>
using namespace std;

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

void sig_int(int signo) {
	pr_mask("\nin sig_int: ");
}

int main(void) {
	sigset_t newmask, oldmask, waitmask;

	pr_mask("program start: ");

	if (signal(SIGINT, sig_int) == SIG_ERR)
		cerr << "signal(SIGINT) error" << endl;
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);
	sigemptyset(&waitmask);
	sigaddset(&waitmask, SIGUSR1);

	// block sigint and save current signal mask
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		cerr << "SIG_BLOCK error" << endl;

	// critical region
	pr_mask("in critical region: ");

	//pause, allowing all signals except SIGUSR1
	if (sigsuspend(&waitmask) != 1)
		cerr << "sigsuspend error" << endl;

	pr_mask("after return from sigsuspend: ");

	// reset signal mask which unblocks sigint
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		cerr << "SIG_SETMASK error" << endl;

	pr_mask("program exit: ");

	return 0;
}
