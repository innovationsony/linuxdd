#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// char *inet_ntoa(struct in_addr in);

#define buffer 2
struct file_s {
	int status;
	char frame[buffer];
};

main()
{
	int sfd = 0;
	int cfd = 0;
	char conifrmation[100] = { '\0' };
	char cl_buffer[100];
	struct sockaddr_in m, cl_addr;
	int ffd;
	struct file_s send;
	socklen_t cl_len = sizeof(struct sockaddr_in);
	if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket_error ");
		exit(10);
	}
	m.sin_family = AF_INET;
	m.sin_port = htons(3000);
	m.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sfd, (struct sockaddr *)&m, sizeof(m)) < 0) {
		perror("bind_error ");
		exit(11);
	}
	if (listen(sfd, 1) < 0) {
		perror("socket listen");
		exit(12);
	}
	if ((cfd = accept(sfd, (struct sockaddr *)&cl_addr, &cl_len)) < 0) {
		perror("accept_error ");
	}

	printf("SERVER:connection established to%u  \nclient addr=%s\n cfd=%d \n ", cl_addr.sin_port,
	       inet_ntoa(cl_addr.sin_addr) ,cfd);
	//opening a xyz file
	if ((ffd = open("test.txt", 0666)) < 0) {
		perror("file_error");
		close(sfd);
		exit(16);
	}
	while (1) {
		if (read(ffd, send.frame, buffer) > 0) {
			send.status = 0;
			write(cfd, &send, sizeof(send));
//                              write(1,&send,sizeof(send));
		} else {
			send.status = 1;
			write(cfd, &send, sizeof(send));
		}
	}
}
