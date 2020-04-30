#include <csignal>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;

void pr_exit(int status) {
	if (WIFEXITED(status))
		cout << "normal termination, exit status = " << WEXITSTATUS(status) << endl;
	else if (WIFSIGNALED(status))
		cout << "abnormal termination, signal number = " << WTERMSIG(status) << ' '
			 << (WCOREDUMP(status) ? "core file generated" : "") << endl;
	else if (WIFSTOPPED(status))
		cout << "child stopped, signal number = " << WSTOPSIG(status) << endl;
}

int main(void) {
	pid_t pid;
	int status;

	if ((pid = fork()) < 0) {
		cerr << "fork error" << endl;
		exit(1);
	} else if (pid == 0)
		exit(7);					// child
	
	if (wait(&status) != pid) {
		cerr << "wait error" << endl;
		exit(1);
	}
	pr_exit(status);


	if ((pid = fork()) < 0) {
		cerr << "fork error" << endl;
		exit(1);
	} else if (pid == 0)
		abort();
	
	if (wait(&status) != pid) {
		cerr << "wait error" << endl;
		exit(1);
	}
	pr_exit(status);


	if ((pid = fork()) < 0) {
		cerr << "fork error" << endl;
		exit(1);
	} else if (pid == 0)
		status /= 0;
	
	if (wait(&status) != pid) {
		cerr << "wait error" << endl;
		exit(1);
	}
	pr_exit(status);

	return 0;
}
