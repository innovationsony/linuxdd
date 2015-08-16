#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

main(){
int sfd=0;
char cl_buffer[100];
char *serverip="127.0.0.1";

struct sockaddr_in m;
struct sockaddr_in cl_addr;
socklen_t cl_len=sizeof(cl_addr);


if((sfd=socket(AF_INET,SOCK_STREAM,0))<0){
 		perror("socket_error ");
	}

//if(bind(sfd, const struct sockaddr *addr,socklen_t addrlen));
// based on which type of domain wew are using
	m.sin_family=AF_INET;
	m.sin_port=htons(3000);
	m.sin_addr.s_addr=htonl(INADDR_ANY);

       if(inet_pton(AF_INET,serverip,&m.sin_addr )<0){
		perror("inetpton");
	}
//int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
//if(connect(sfd,(struct sockaddr_in*)&m,sizeof(struct sockaddr_in))<0){
if(connect(sfd,(struct sockaddr*)&m,(cl_len))<0){
	perror("connect");

}
		printf("CONNECTION ESTABLISHED ");

	read(sfd,cl_buffer,sizeof(cl_buffer));
	 write(1,cl_buffer,10);
	write(sfd,"operation_completed",19);
//if(listen(sfd,2)<0)
//	{	perror("socket listen");}
//}



}
