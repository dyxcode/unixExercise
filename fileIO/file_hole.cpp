#include <cstdio>
#include <unistd.h>
#include <fcntl.h>

#include <iostream>
#include <string>

int main(void) {
	int fd = open("file.hole", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		std::cerr << "create error" << std::endl;

	if (write(fd, "abc", 3) != 3)
		std::cerr << "write error" << std::endl;

	if (lseek(fd, 16384, SEEK_SET) == -1)
		std::cerr << "lseek error" << std::endl;

	if (write(fd, "123", 3) != 3)
		std::cerr << "write second error" << std::endl;


	return 0;
}
