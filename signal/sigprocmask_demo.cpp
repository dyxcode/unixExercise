#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>
using namespace std;

void sig_quit(int signo) {
	cout << "caught SIGQUIT" << endl;
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR) {
		cerr << "can't reset SIGQUIT" << endl;
		exit(1);
	}
}

int main(void) {
	sigset_t newmask, oldmask, pendmask;

	if (signal(SIGQUIT, sig_quit) == SIG_ERR) {
		cerr << "can't catch SIGQUIT" << endl;
		exit(1);
	}
	// block sigquit and save current signal mask
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
		cerr << "sigprocmask(SIG_BLOCK) error" << endl;
		exit(1);
	}
	sleep(5); //sigquit here will remain pending

	if (sigpending(&pendmask) < 0) {
		cerr << "sigpending error" << endl;
		exit(1);
	}
	if (sigismember(&pendmask, SIGQUIT))
		cout << "SIGQUIT pending" << endl;

	//restore signal mask which unblocks sigquit
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
		cerr << "sigprocmask(SIG_SETMASK) error" << endl;
		exit(1);
	}
	cout << "SIGQUIT unblocked" << endl;

	sleep(5); //sigquit here will terminate with core file

	return 0;
}
