// Client Side

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define PORT 8080
#define MAX 100


void Chat(int sockfd){
	char buffer[MAX];
	int chars;
	while(1){
		bzero(buffer,sizeof(buffer));
		printf("Say Something : ");
		chars=0;
		while ((buffer[chars++] = getchar()) != '\n');
			
		write(sockfd,buffer,sizeof(buffer));
		bzero(buffer,sizeof(buffer));
		read (sockfd,buffer,sizeof(buffer));
		printf("Server replied : %s",buffer);
		if (( strncmp(buffer,"exit", 4)) == 0){
			printf("Exiting the Client..\n");
			break;
		}
			
	}	

}
int main(){
	// socket descriptor
	int sockfd=0;
	struct sockaddr_in server_address,clnt;
	
	// creating a socket
	// domain = AF_INET - IPv4 protocol
	// type = TCP (SOCK_STREAM)
	// protocol = IP (Internet Protocol) = 0
	// sockfd = socket descriptor int
	
	sockfd = socket(AF_INET,SOCK_STREAM,0) ;
	if ( sockfd < 0){
		printf("\nError in Socket Creation!\n");
		return -1;
	}
	else{
		printf("Socket Creation Successful!\n");
	}
	// clears buffer
	bzero(&server_address,sizeof(server_address));
	
	// assigning port and IP type
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT); // port = 8080
	
	if (inet_pton(AF_INET,"192.168.137.28",&server_address.sin_addr) <= 0){
		printf("Error! Invalid Address or Address not supported!\n");
		return -1;
	}
	else{
		printf("Successfully converted address to binary form!");
	}
	
	// connection
	if (connect(sockfd,(struct sockaddr *)&server_address, sizeof(server_address)) < 0){
		printf("\nError! Connection Failed...\n");
		return -1;
	}
	else{
		printf("Server Connected Successfully!\n");
	}
	// Communication with server
	Chat(sockfd);
	// socket closed
	close(sockfd);

	return 0;
}
