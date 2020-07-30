#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/time.h>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

constexpr int MAXLINE = 1024;
char buf[MAXLINE];

void str_cli(FILE *fp, int sockfd) {
	fd_set rset;
	FD_ZERO(&rset);

	bool stdinEOF = false;
	while (1) {
		if (stdinEOF == false)
			FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);
		
		int maxfd = max(fileno(fp), sockfd) + 1;
		if (select(maxfd, &rset, nullptr, nullptr, nullptr) < 0) {
			cerr << "select error" << endl;
			exit(1);
		}

		if (FD_ISSET(sockfd, &rset)) {
			int n = read(sockfd, buf, MAXLINE);
			if (n == 0) {
				if (stdinEOF == true)
					return ;
				else {
					cerr << "client error : server terminated prematurely" << endl;
					exit(1);
				}
			}
			write(fileno(stdout), buf, n);
		}

		if (FD_ISSET(fileno(fp), &rset)) {
			int n = read(fileno(fp), buf, MAXLINE);
			if (n == 0) {
				stdinEOF = true;
				shutdown(sockfd, SHUT_WR);
				FD_CLR(fileno(fp), &rset);
				continue;
			}
			write(sockfd, buf, n);
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cerr << "usage : tcpclient <IPaddress>" << endl;
		exit(1);
	}

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		cerr << "socket error" << endl;
		exit(1);
	}

	sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8888);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	if (0 != connect(sockfd, reinterpret_cast<sockaddr*>(&servaddr), sizeof(servaddr))) {
		cerr << "connect error" << endl;
		exit(1);
	}

	str_cli(stdin, sockfd);

	return 0;
}
