// server program for udp connection 
#include <stdio.h> 
#include <strings.h> 
#include <sys/types.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include<netinet/in.h> 
#include <stdlib.h>
#include<unistd.h>
#define PORT 5000 
#define MAXLINE 1000 
#define LISTENQ 8 
// Driver code 
int main() 
{ 
	char buffer[100]; 
	char *message = "Hello Client"; 
	int listenfd, len; 
     pid_t childpid;
	struct sockaddr_in servaddr, cliaddr; 
	bzero(&servaddr, sizeof(servaddr)); 

	// Create a UDP Socket 
	listenfd = socket(AF_INET, SOCK_DGRAM, 0);		 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_family = AF_INET; 

	// bind server address to socket descriptor 
	bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 
	 listen (listenfd, LISTENQ);
	//receive the datagram 
	len = sizeof(cliaddr); 

      if ( (childpid = fork()) == 0 ) {
      exit(0);  // child terminates
    }
	int n = recvfrom(listenfd, buffer, sizeof(buffer), 
			0, (struct sockaddr*)&cliaddr,&len); //receive message from server 
	buffer[n] = '\0'; 
	puts(buffer); 
		
	// send the response 
	sendto(listenfd, message, MAXLINE, 0, 
		(struct sockaddr*)&cliaddr, sizeof(cliaddr)); 
} 
