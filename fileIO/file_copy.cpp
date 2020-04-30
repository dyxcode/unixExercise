#include <ostream>
#include <unistd.h>
#include <iostream>

#define BUFFSIZE 4096

int main(void) {
	int n;
	char buf[BUFFSIZE];

	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
		if (write(STDOUT_FILENO, buf, n) != n)
			std::cerr << "write error" << std::endl;

	if (n < 0)
		std::cerr << "read error" << std::endl;

	return 0;
}
