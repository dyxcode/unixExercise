#include <cstddef>
#include <cstdio>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
using namespace std;

constexpr int MAXLINE = 1024;
char sendline[MAXLINE], recvline[MAXLINE+1];

void dg_cli(FILE* fp, int sockfd, const sockaddr* pservaddr, socklen_t servlen) {
	while (fgets(sendline, MAXLINE, fp) != NULL) {
		sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
		int n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
		recvline[n] = '\0';
		fputs(recvline, stdout);
	}
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cerr << "usage : udpclient <IPaddress>" << endl;
		exit(1);
	}

	sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8888);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	dg_cli(stdin, sockfd, reinterpret_cast<sockaddr*>(&servaddr), sizeof(servaddr));

	return 0;
}
