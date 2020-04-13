#include "cliserv.h"

int main(int argc, char *argv[]) {
	struct sockaddr_in serv;
	char request[REQUEST], reply[REPLY];
	int sockfd, n, i;

	if (argc != 2)
		err_quit("usage: udpcli <IP address of server>]\n");
	if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
		err_sys("socket error\n");
	}

	memset(&serv, 0, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr(argv[1]);
	serv.sin_port = htons(UDP_SERV_PORT);

	for (i = 0; i < REQUEST; i++) {
		request[i] = 'a' + i % 10;
	}
	request[REQUEST - 1] = '\0';
	printf("client request %s\n", request);

	if (sendto(sockfd, request, REQUEST, 0, (SA)&serv, sizeof(serv)) != REQUEST) {
		err_sys("sendto error\n");
	}

	if ((n = recvfrom(sockfd, reply, REPLY, 0, NULL, (int *)NULL)) < 0)
		err_sys("recvfrom error\n");
	exit(0);
}