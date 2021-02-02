#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#define PORT 8080

// TCP CONNECTION Client Side

int main(int argc,char const *argv[]){
	int sock = 0,valread;
	struct sockaddr_in servaddr;
	char *hello = "Hello from Client";
	char buffer[1024] = {0};
	
	
	if ((sock = socket(AF_INET,SOCK_STREAM,0)) < 0){
		printf("\nSocket Creation Error!\n");
		return -1;
	}
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	
	if (inet_pton(AF_INET,"192.168.43.248",&servaddr.sin_addr) <= 0){
		printf("Error! Invalid Address or Address not supported!\n");
		return -1;
	}
	else{
		printf("Successfully converted address to binary form!");
	}
	if (connect(sock,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0){
		printf("\nConnection Failed\n");
		return -1;
	}
	send(sock,hello,strlen(hello),0);
	printf("Hello Message sent to server!\n");
	valread = read(sock,buffer,1024);
	printf("%s\n",buffer);

	return 0;
}
