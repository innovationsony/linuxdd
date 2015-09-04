#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <netinet/ip.h>

main(){
int sfd=0;int cfd=0;
char buffer[100]="asdkfhksjdfhjkads";
char cl_buffer[100];
struct sockaddr_in m;
//for c
struct sockaddr_in cl_addr;

socklen_t cl_len=sizeof(struct sockaddr_in);
if((sfd=socket(AF_INET,SOCK_STREAM,0))<0){
 	perror("socket_error ");
}

//if(bind(sfd, const struct sockaddr *addr,socklen_t addrlen));
// based on which type of domain wew are using
	
	m.sin_family=AF_INET;
	m.sin_port=htons(3000);
	m.sin_addr.s_addr=htonl(INADDR_ANY);

if(bind(sfd,(struct sockaddr *) &m,sizeof(m))<0)
	{ perror("bind_error "); }

if(listen(sfd,2)<0)
	{	perror("socket listen");}

 if((cfd=accept(sfd, (struct sockaddr *)&cl_addr, &cl_len))<0)
	{ perror("accept_error "); }
	printf("connection established to %u\n",cl_addr.sin_port);
	printf("cfd=%d\n",cfd);
	write(cfd,buffer,10);
	read(cfd,cl_buffer,sizeof(cl_buffer));
	write(1,cl_buffer,19);
}
