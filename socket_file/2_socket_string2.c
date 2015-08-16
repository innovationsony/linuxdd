#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
 #include <netinet/ip.h>
#include<fcntl.h>
#define buffer 2
struct  file_s{
        int status;
        char frame[buffer];
};


main(){
int sfd=0;
int cfd=0;
char cl_buffer[100];
struct sockaddr_in m;
struct sockaddr_in cl_addr;
struct file_s  recv;
int ffd;
	socklen_t cl_len=sizeof(struct sockaddr_in);
	if((sfd=socket(AF_INET,SOCK_STREAM,0))<0)
							{ 	perror("socket_error ");}
	m.sin_family=AF_INET;
	m.sin_port=htons(3000);
	m.sin_addr.s_addr=htonl(INADDR_ANY);
if(bind(sfd, (struct sockaddr *) &m,sizeof(m))<0)
							{ perror("bind_error "); }
if(listen(sfd,1)<0)
							{	perror("socket listen");}
 if((cfd=accept(sfd, (struct sockaddr *)&cl_addr, &cl_len))<0)
							{ perror("accept_error "); }
	printf("connection established to %u\n",cl_addr.sin_port);
	printf("cfd=%d\n",cfd);

//  connection established
	if((ffd=open("xyz.txt",O_CREAT | O_RDWR | O_TRUNC ,0666))<0)
							{ perror("open file_error "); }
	while(1){
		read(sfd,&recv,sizeof(recv));
			if(!recv.status)
			write(ffd,recv.frame,buffer);
		else
		      break;
	}
}
