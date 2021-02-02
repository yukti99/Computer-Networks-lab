// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#define PORT 8080 
#define MAX_BUF 1024 



int main(){
	int sockfd;
	char buffer[MAX_BUF];
	struct sockaddr_in server_address,cliaddr;
	
	// creating the socket 
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if (sockfd < 0){
		printf("Socket Creation Failed!\n");
		return -1;
	}
	else{
		printf("Socket Created Successfully!\n");
	}
	// filling Server Information
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(PORT);
	
	// Bind the socket with server address
	if (bind(sockfd,(struct sockaddr*)&server_address,sizeof(server_address)) < 0){
		printf("Binding Failed...");
		return -1;
	}else{
		printf("Binding done!\n");
	}
	
	int len,n;
	// receive data packets  
	// MSG - blocks further activity until full request is satisfied
	n = recvfrom(sockfd,(char*)buffer,MAX_BUF,MSG_WAITALL,(struct sockaddr *)&cliaddr,&len);
	buffer[n] = '\0';
	printf("Client : %s\n",buffer);
	const char *msg = "Hello from Server";
	sendto(sockfd,msg,strlen(msg),MSG_CONFIRM,(const struct sockaddr*)&cliaddr,len);
	printf("Message Sent to client!\n");	
	
	return 0;
}
