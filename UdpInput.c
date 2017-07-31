#include "common.h"
#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUFLEN 2*sizeof(int)
#define PORT 8888

void die(const char *s)
{
	printf(s);
	fflush(stdout);
	exit(1);
}

int main()
{
	common::init(O_WRONLY);

	struct sockaddr_in si_me, si_other;
	int s, i, recv_len;
	unsigned int slen = sizeof(sockaddr_in);
	char buf[BUFLEN];

	//create a UDP socket
    	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    	{
        	die("socket");
    	}

    	// zero out the structure
    	memset((char *) &si_me, 0, sizeof(si_me));

    	si_me.sin_family = AF_INET;
    	si_me.sin_port = htons(PORT);
    	si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    	//bind socket to port
    	if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    	{
        	die("bind");
    	}

	common::additionalFdToClose = s;

	while(true)
	{
		printf("\nWaiting for data...");
	        fflush(stdout);

	        //try to receive some data, this is a blocking call
        	if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
        	{
	            	die("\nDIE recvfrom()");
        	}

	        //print details of the client/peer and the data received
        	printf("\nReceived packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
	        printf("\nData: %s\n" , buf);

		printf("\nChanged state to %d on pin %d", *((int*)buf), ((int*)buf)[1] );
		fflush(stdout);
		common::write( *((int*)buf), ((int*)buf)[1]);

		delay(100);
	}
	return 0;
}
