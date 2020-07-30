#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <cstring>
#include <unistd.h>
#include <iostream>
using namespace std;

constexpr int MAXLINE = 1024;
char buf[MAXLINE];

int main(int argc, char *argv[]) {
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd < 0) {
		cerr << "socket error" << endl;
		exit(1);
	}
	
	sockaddr_in cliaddr, servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(8888);

	if (0 != bind(listenfd, reinterpret_cast<sockaddr*>(&servaddr), sizeof(servaddr))) {
		cerr << "bind error" << endl;
		exit(1);
	}

	if (0 != listen(listenfd, 128)) {
		cerr << "listen error" << endl;
		exit(1);
	}

	int maxfd = listenfd;
	int maxi = -1;
	int client[FD_SETSIZE];
	for (int i = 0; i < FD_SETSIZE; ++i)
		client[i] = -1;

	fd_set allset;
	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);

	while (1) {
		fd_set rset = allset;
		int nready = select(maxfd + 1, &rset, nullptr, nullptr, nullptr);
		if (nready < 0) {
			cerr << "select error" << endl;
			exit(1);
		}
		if (FD_ISSET(listenfd, &rset)) {
			socklen_t clilen = sizeof(cliaddr);
			int connfd = accept(listenfd, reinterpret_cast<sockaddr*>(&cliaddr), &clilen);
			int i;
			for (i = 0; i < FD_SETSIZE; ++i)
				if (client[i] < 0) {
					client[i] = connfd;
					break;
				}
			if (i == FD_SETSIZE) {
				cerr << "too many clients" << endl;
				exit(1);
			}

			FD_SET(connfd, &allset);
			maxfd = max(maxfd, connfd);
			maxi = max(maxi, i);
			if (--nready <= 0)
				continue;
		}
		
		for (int i = 0; i <= maxi; ++i) {
			int sockfd = client[i];
			if (sockfd < 0)
				continue;
			if (FD_ISSET(sockfd, &rset)) {
				int n = read(sockfd, buf, MAXLINE);
				if (n == 0) {
					close(sockfd);
					FD_CLR(sockfd, &allset);
					client[i] = -1;
				}
				else
					write(sockfd, buf, n);
			
				if (--nready <= 0)
					break;
			}
		}
	}

	return 0;
}
