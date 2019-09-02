#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define HOST "ifconfig.me"
int main()
{
    char *hostname;
    struct hostent *host;
    struct sockaddr_in ifconfig;
    int sockfd, treat,ascii=0,lines=0,pos_a=0,pos_b=0;
	char externip[15] = "";
    char buffer[400] = "";
    host = gethostbyname(HOST);
    hostname = inet_ntoa(*(struct in_addr*)host->h_addr_list[0]);
    if(host==NULL)
    {
        printf("Cant connect on the searcher host\n");
        exit(1);
    }
    printf("	----------------------------------------------------\n");
    printf("	Trying reversing Web connection on %s\n",host->h_name);
    printf("	IP: %s\n",inet_ntoa(*(struct in_addr*)host->h_addr_list[0]));
    ifconfig.sin_family = AF_INET;
    ifconfig.sin_addr.s_addr = inet_addr(hostname); 
    ifconfig.sin_port = htons(80);
    memset(ifconfig.sin_zero,0,strlen(ifconfig.sin_zero));
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd == -1)
    {
        printf("	socket: error\n");
        exit(1);
    }
    treat = connect(sockfd,(struct sockaddr*)&ifconfig,sizeof(ifconfig));
	if(treat == -1)
	{
		printf("	connect: without connection\n");
		exit(1);
	}
	send(sockfd,"GET / HTTP/1.1\nHost: ifconfig.me\n\n",strlen("GET / HTTP/1.1\nHost: ifconfig.me\n\n"),0);
	printf("	Request sent\n");
	recv(sockfd,buffer,sizeof(buffer),0);
	pos_b = strlen(buffer)-15;
	while(pos_b<strlen(buffer))
	{
		externip[pos_a] = buffer[pos_b];
		int critic(char);
		treat = critic(externip[pos_a]);
		if(treat == 1)
		{
			memset(&externip[pos_a],32,1);
		}
		pos_a++;
		pos_b++;
	}
	printf("	Your extern ip: ");
	printf("%s",externip);
	printf("\n	----------------------------------------------------\n");
	close(sockfd);
	exit(1);
}
int critic(char ascii)
{
	for(int numbers=48;numbers<=57;numbers++)
	{
		if(ascii==numbers)
		{
			return 0;
		}
	}
	if(ascii ==  46)
	{
			return 0;
	}
	return 1;
}