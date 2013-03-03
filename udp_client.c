/*senderprog.c - a client, datagram*/
//#include "msgTYPE.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include"buffertostruct.h"
// #include < time.h >
#include <netdb.h>
/* the port users will be connecting to */
#define MYPORT 4951
#define LINELEN 127
#define STDIN 0
//#define STDOUT 1
int main(int argc, char *argv[])
{
	int sockfd;
	fd_set readfds,writefds;
	int rval;
	struct sockaddr_in their_addr;
	im_message my,revmsg;
	struct hostent *he;
	int numbytes;
	char *send_buffer = malloc(sizeof(im_message));
	char rev_buffer[1024]; 
	if (argc != 4)
	{
		fprintf(stderr, "Client-Usage: %s <usere> <hostname> <port>\n", argv[0]);
		exit(1);
	}
	strcpy(my.from,argv[1]);
	if (( he = gethostbyname(argv[2])) == NULL)
	{
		perror("Client-gethostbyname() error lol!");
		exit(1);
	}
	else{}
	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons((unsigned short)atoi(argv[3]));
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	memset(&(their_addr.sin_zero), '\0', 8);
		if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("Client-socket() error lol!");
		exit(1);
	}
	else{}
	FD_ZERO(&readfds);
	FD_SET(STDIN,&readfds);
	FD_SET(sockfd,&readfds);  
	int addr_len = sizeof(struct sockaddr);
	char buf[sizeof(im_message)];
	if((numbytes = sendto(sockfd,&my,sizeof(my), 0, (struct sockaddr *)&their_addr, sizeof(struct sockaddr))) == -1)
	{
		perror("Client-sendto() error lol!");
		exit(1);
	}
	else{
	}
	while(1)
	{  
		printf("%s> ",argv[1]);
		fflush(stdout);
		FD_ZERO(&readfds);
		FD_SET(STDIN,&readfds);
		FD_SET(sockfd,&readfds); 
		rval = select(sizeof(readfds)+1, &readfds,NULL, NULL, NULL);
		if(FD_ISSET(STDIN,&readfds))
		{
			if (read(STDIN, buf, sizeof(im_message)-1) < 0)
			printf("socket read failed: \n");
			buf[sizeof(im_message)-1] = '\0';	
			if(bufferTostruct(buf, &my,argv[1])>0)
			{
				int nchars = strlen(buf);
				if((numbytes = sendto(sockfd,&my, sizeof(im_message), 0, (struct sockaddr *)&their_addr, sizeof(struct sockaddr))) == -1)
				{
					perror("Client-sendto() error lol!");
					exit(1);
				}
				else{
					}   
				if(my.type==DEREGISTRATION_MESSAGE)
				{
					printf("THANKS FOR USING OUR SERVICES\n\n\n");
					exit(1);  	
				}
			}
			else
			{
				printf("PLEASE ENTER RECIEVER USERNAME\n");
			}

		}
		if(FD_ISSET(sockfd,&readfds))
		{ 
			if((numbytes = recvfrom(sockfd,&revmsg, sizeof(im_message), 0, (struct sockaddr *)&their_addr, &addr_len)) == -1)
			{
				perror("Server-recvfrom() error lol!");
				exit(1);
			}	
			else
			{
				printf("%s %s",revmsg.from,revmsg.message);
				fflush(stdout);
				memset(revmsg.message,'\0',sizeof(revmsg.message));
			}
		}

	}

}
