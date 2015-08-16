/*
	when connection established

	-------------------------------------------
	accept                              
                 ---blocked                                  server block released by client connection
								create a xyz file
 (block relesed)when ever client connects 
server opens xyz.txt file                                   
                
                read xyz file                                                
          write to client fd                                   read from socket fd
								        write to created file

HINT : USE A STRUCTURE
*/


#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <netinet/ip.h>
struct  file_s{
	int status;
	char frame[2];	
};

main(){
int sfd=0;int cfd=0;
char buffer[100]="connection established to server";
char conifrmation[100]={'\0'};
char cl_buffer[100];
struct sockaddr_in m;
int ffd;
struct file_s send={0,{'\0'}};
//for c
struct sockaddr_in cl_addr;
socklen_t cl_len=sizeof(struct sockaddr_in);
if((sfd=socket(AF_INET,SOCK_STREAM,0))<0){
 	perror("socket_error "); exit(10);
}
//if(bind(sfd, const struct sockaddr *addr,socklen_t addrlen));
// based on which type of domain wew are using
	m.sin_family=AF_INET;
	m.sin_port=htons(3000);
	m.sin_addr.s_addr=htonl(INADDR_ANY);
if(bind(sfd, (struct sockaddr *) &m,sizeof(m))<0)
								{       perror("bind_error "); exit(11);  }
if(listen(sfd,1)<0)
								{	perror("socket listen"); exit(12);}
 if((cfd=accept(sfd, (struct sockaddr *)&cl_addr, &cl_len))<0)
								{ perror("accept_error "); }
	printf("SERVER:connection established to%u  %d \n ",cl_addr.sin_port,cfd);
	

	//opening a xyz file
	if((ffd=open("xyz.txt",0666))<0)
							{perror("file_error"); close(sfd);exit(16);}

	if(read(ffd,send.frame,2)>=0)
		{		     
			send.status=0; 
			write(cfd,&send,sizeof(send));}
	else  {
			send.status=1;
			write(cfd,&send,sizeof(send));}
		
	

//	write(cfd,confirmation,10);


}
