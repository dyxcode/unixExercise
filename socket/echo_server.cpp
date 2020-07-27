#include <asm-generic/errno-base.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;

void str_echo(int sockfd) {
	size_t n;
	char buf[128];

	while (1) {
		while ((n = read(sockfd, buf, 128)) > 0)
			write(sockfd, buf, n);

		if (n < 0 && errno == EINTR)
			continue;
		else
			break;
	}
}

int main() {
	int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(8888);

	bind(listen_fd, reinterpret_cast<sockaddr*>(&servaddr), sizeof(servaddr));
	listen(listen_fd, 128);

	while (1) {
		sockaddr_in cliaddr;
		socklen_t clilen = sizeof(cliaddr);
		int connfd = accept(listen_fd, reinterpret_cast<sockaddr*>(&cliaddr), &clilen);
		cout << "client connect, connfd : " << connfd << endl;
		pid_t childpid;

		if ((childpid = fork()) == 0) {
			close(listen_fd);
			str_echo(connfd);
			exit(0);
		}
		close(connfd);
	}
	return 0;
}
