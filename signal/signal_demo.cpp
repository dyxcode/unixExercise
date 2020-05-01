#include <unistd.h>
#include <signal.h>
#include <iostream>
using namespace std;

void sig_usr(int signo) {
	if (signo == SIGUSR1)
		cout << "received SIGUSR1" << endl;
	else if (signo == SIGUSR2)
		cout << "received SIGUSR1" << endl;
	else
		cout << "received signal : " << signo << endl;
}

int main(void) {
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
		cerr << "can't catch SIGUSR1" << endl;
	if (signal(SIGUSR2, sig_usr) == SIG_ERR)
		cerr << "can't catch SIGUSR2" << endl;
	for ( ; ; )
		pause();
	return 0;
}
