#include <csignal>
#include <iostream>
#include <sys/select.h>
#include <unistd.h>
#include <signal.h>
using namespace std;

#define BUFFSIZE 1024

void sig_tstp(int signo) {
	sigset_t mask;

	// move cursor to lower left corner, reset tty mode
	
	// unblock sigtstp, since it's blocked while we're handling it
	sigemptyset(&mask);
	sigaddset(&mask, SIGTSTP);
	sigprocmask(SIG_UNBLOCK, &mask, NULL);
	
	// reset disposition to default
	signal(SIGTSTP, SIG_DFL);
	// and send the signal to ourself
	kill(getpid(), SIGTSTP);

	// we won't return from the kill until we're continued
	
	signal(SIGTSTP, sig_tstp);

	// reset tty mode, redraw screen
}

int main(void) {
	int n;
	char buf[BUFFSIZE];

	// only catch sigtstp if we're running with a job-control shell
	
	if (signal(SIGTSTP, SIG_IGN) == SIG_DFL)
		signal(SIGTSTP, sig_tstp);

	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
		if (write(STDOUT_FILENO, buf, n) != n)
			cerr << "write error" << endl;

	if (n < 0)
		cerr << "read error" << endl;

	return 0;
}
