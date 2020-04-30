#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

const char *env_init[] = { "USER=unknwon", "PATH=/tmp", NULL };

int main(void) {
	pid_t pid;

	if ((pid = fork()) < 0) {
		cerr << "fork error" << endl;
		exit(1);
	} else if (pid == 0) {
		if (execle("/home/dyx/githubCode/unixExercise/processControl/echoall",
					"echoall", "myarg1", "MY ARG2", (char *)0, env_init) < 0) {
			cerr << "execle error" << endl;
			exit(1);
		}
	}

	if (waitpid(pid, NULL, 0) < 0) {
		cerr << "waitpid error" << endl;
		exit(1);
	}

	return 0;
}
