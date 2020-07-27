#include <cstdio>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

int main() {
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		perror("socket error");
		exit(1);
	}

	sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8888);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int ret = bind(fd, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr));
	if (ret < 0) {
		perror("bind error");
		exit(1);
	}

	cout << "fd = " << fd << endl;
	return 0;
}
