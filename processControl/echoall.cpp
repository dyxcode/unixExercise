#include <unistd.h>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	extern char **environ;

	for (size_t i = 0; i < argc; i++)
		cout << "argv[" << i << "]: " << argv[i] << endl;
	for (char **ptr = environ; *ptr != 0; ptr++)
		cout << *ptr << endl;

	return 0;
}
