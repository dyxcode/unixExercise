#include <csignal>
#include <unistd.h>
#include <iostream>

static volatile sig_atomic_t sigflag;
static sigset_t newmask, oldmask, zeromask;

static void
sig_usr(int signo) {
	sigflag = 1;
}

void TELL_WAIT(void) {
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
		std::cerr << "signal(SIGUSR1) error" << std::endl;
	if (signal(SIGUSR2, sig_usr) == SIG_ERR)
		std::cerr << "signal(SIGUSR2) error" << std::endl;
	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGUSR1);
	sigaddset(&newmask, SIGUSR2);

	// block sigusr1 and sigusr2, and save current signal mask
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		std::cerr << "SIG_BLOCK error" << std::endl;
}

void
TELL_PARENT(pid_t pid) {
	kill(pid, SIGUSR2);
}

void
WAIT_PARENT(void) {
	while (sigflag == 0)
		sigsuspend(&zeromask);
	sigflag = 0;

	// reset signal mask to original value
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		std::cerr << "SIG_SETMASK error" << std::endl;
}

void
TELL_CHILD(pid_t pid) {
	kill(pid, SIGUSR1);
}

void
WAIT_CHILD(void) {
	while (sigflag == 0)
		sigsuspend(&zeromask);
	sigflag = 0;

	// reset signal mask to original value
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		std::cerr << "SIG_SETMASK error" << std::endl;
}
