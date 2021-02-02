// Client side implementation of UDP client-server model 
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
	struct sockaddr_in server_address;
	const char *msg = "Hello from Client!";
	
	// creating socket file descriptor
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if (sockfd < 0){
		printf("Error in Socket Creation!\n");
		return -1;
	}else{
		printf("Socket Created Successfully\n");
	}
	memset(&server_address, 0, sizeof(server_address)); 
	
	// Filling server information
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(PORT);
	
	int n,len;
	// sending message to server
	sendto(sockfd,msg,strlen(msg),MSG_CONFIRM,(const struct sockaddr*)&server_address,sizeof(server_address));
	printf("Message sent to the Server!\n");
	
	// receiving message fromt the server
	n = recvfrom(sockfd,buffer,MAX_BUF,MSG_WAITALL,(struct sockaddr*)&server_address,&len);
	buffer[n] = '\0';
	printf("Server : %s\n",buffer);
	
	//socket closed by client
	close(sockfd);
}
	
