#include <unistd.h>
#include <cstdlib>
#include <pthread.h>
#include <iostream>
using namespace std;

pthread_t ntid;

void printids(const char *s) {
	pid_t pid;
	pthread_t tid;

	pid = getpid();
	tid = pthread_self();
	cout << s << '\n' << "pid:" << pid << " tid:" << tid << endl;
}

void* thr_fn(void *arg) {
	printids("new thread: ");
	return (void *)0;
}

int main() {
	int err;

	err = pthread_create(&ntid, NULL, thr_fn, NULL);
	if (err != 0) {
		cerr << "can't create thread" << endl;
		exit(1);
	}
	printids("main thread:");
	sleep(1);
	return 0;
}
