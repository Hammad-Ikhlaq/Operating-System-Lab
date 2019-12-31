#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include<stdio.h>
/*
struct in_addr 
{
    unsigned long s_addr;  // load with inet_aton()
};
struct sockaddr
{
	unsigned short sa_family; //address family AF_xxx 
	unsigned short sa_data[14]; //14 bytes of protocol addr 
}

struct sockaddr_in
{

	short int sin_family; // set to AF_INET 
	unsigned short int sin_port; // port number 
	in_addr sin_addr; // internet address 
	unsigned char sin_zero[8]; //set to all zeros 
}
*/
int main()
{
	int sd;
	char msg[1000];	
	sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(4997);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	sd = socket(AF_INET,SOCK_STREAM,0);
	
	connect(sd, (struct sockaddr *)&server_addr, sizeof(sockaddr));

	recv(sd,msg,100,0);
	printf("%s\n",msg);

	return 0;
	
}
