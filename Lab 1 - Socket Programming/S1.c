// Server Side

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h> 
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define PORT 8080
#define MAX 100

void Chat(int sockfd){
	char buffer[MAX];
	int chars;
	while(1){
		bzero(buffer,sizeof(buffer));
		// read message from client and store it in buffer
		read(sockfd,buffer,sizeof(buffer));	
		printf("Client said : %s ",buffer);
		bzero(buffer,MAX);
		chars = 0;		
		printf("Say something to send to client : ");
		while ((buffer[chars++] = getchar()) != '\n');
		
		// send the buffer to client 
		write(sockfd,buffer,sizeof(buffer));
		
		if (( strncmp(buffer,"exit", 4)) == 0){
			printf("Exiting the Server..\n");
			break;
		}		
	}	

}
int main(){
	// socket descriptor
	int sockfd=0,connfd,len;
	struct sockaddr_in server_address,clnt;
	char buffer[1024] = {0};

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
	//  gives IP address automatically
	server_address.sin_addr.s_addr = INADDR_ANY;
	
	// Binding newly created socket to given IP and verification
	if ((bind(sockfd,(struct sockaddr *)&server_address,sizeof(server_address))) != 0){
		printf("Socket bind Failed...\n");
		return -1;
	}
	else{
		printf("Socket successfully binded..\n"); 
	}
	
	// Server listen
	if ((listen(sockfd, 5)) != 0) { 
        	printf("Listen failed...\n"); 
        	return -1;
	} 
	else
        	printf("Server listening..\n"); 
        	
        len = sizeof(clnt); 
        // Accept the data packet from client and verification 
        connfd = accept(sockfd, (struct sockaddr *)&clnt, &len); 
        if (connfd < 0) { 
		printf("Server acccept failed...\n"); 
		return -1;
	} 
	else{
		printf("Server acccept the client...\n"); 
	}
	  
	// Function for chatting between client and server 
	Chat(connfd); 
	  
	// Socket closed after the chat
	close(sockfd);        
	
	// Connection
	if (connect(sockfd,(struct sockaddr *)&server_address, sizeof(server_address)) < 0){
		printf("\nConnection Failed...\n");
		return -1;
	}
	else{
		printf("Server Connected Successfully!\n");
	}
	int valread = read(connfd,buffer,1024);
	printf("%s\n",buffer);
	send(connfd,"hello from server",strlen("hello from server"),0);
	printf("Hello message sent!\n");

	return 0;
}
