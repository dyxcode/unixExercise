#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
using namespace std;

constexpr int MAXLINE = 1024;
char mesg[MAXLINE];

void dg_echo(int sockfd, sockaddr *pcliaddr, socklen_t clilen) {
	while (1) {
		socklen_t len = clilen;
		int n = recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);
		sendto(sockfd, mesg, n, 0, pcliaddr, len);
	}
}

int main(int argc, char *argv[]) {
	int sockfd;
	sockaddr_in servaddr, cliaddr;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(8888);

	bind(sockfd, reinterpret_cast<sockaddr*>(&servaddr), sizeof(servaddr));

	dg_echo(sockfd, reinterpret_cast<sockaddr*>(&cliaddr), sizeof(cliaddr));

	return 0;
}
