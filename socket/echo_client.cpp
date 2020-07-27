#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

int main(int argc, char *argv[]) {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8888);
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
	connect(sockfd, reinterpret_cast<sockaddr*>(&servaddr), sizeof(servaddr));

	char sendline[128], recvline[128];
	while (fgets(sendline, 128, stdin) != NULL) {
		write(sockfd, sendline, strlen(sendline));
		if (read(sockfd, recvline, 128) == 0) {
			cerr << "server quit" << endl;
			exit(0);
		}
		cout << recvline << endl;
	}
	return 0;
}
