#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include<string.h>
#include<fcntl.h>
#define buffer 2
struct  file_s{
        int status;
        char frame[buffer];
};
main(){
int sfd=0;
char cl_buffer[100];
//char *serverip="127.0.0.1";
char *serverip="192.168.0.102";
struct file_s recv;
memset(&recv,0,sizeof(struct file_s));
struct sockaddr_in m;
struct sockaddr_in cl_addr;
socklen_t cl_len=sizeof(cl_addr);
//int recv;
int ffd;
	if((sfd=socket(AF_INET,SOCK_STREAM,0))<0){
 		perror("socket_error ");
	}
	m.sin_family=AF_INET;
	m.sin_port=htons(3000);
	m.sin_addr.s_addr=htonl(INADDR_ANY);
       if(inet_pton(AF_INET,serverip,&m.sin_addr )<0){
		perror("inetpton");
	}

	if(connect(sfd,(struct sockaddr*)&m,(cl_len))<0){
		perror("connect");
	}
	printf("CONNECTION ESTABLISHED ");
//conection established
        if((ffd=open("xyz.txt",O_CREAT | O_RDWR | O_TRUNC,0666))<0)
                                                        { perror("open file_error ");exit(17); }
        while(1){
                read(sfd,&recv,sizeof(recv));
                        if(!recv.status){
                        	write(ffd,recv.frame,buffer);
			}
                else
                      break;
        }
}
