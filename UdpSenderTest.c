#include <stdio.h> //printf
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER "127.0.0.1"
#define BUFLEN 2*sizeof(int)  //Max length of buffer
#define PORT 8888   //The port on which to send data
 
void die(const char *s)
{
	printf(s);
	fflush(stdout);
	exit(1);
}
 
int main(int argc, char ** argv)
{
    struct sockaddr_in si_other;
    int s, i;
    unsigned int slen = sizeof(sockaddr_in);
    char buf[BUFLEN];
    char message[BUFLEN];

    *((int*)message) = (int)atoi(argv[1]);
    ((int*)message)[1] = (int)atoi(argv[2]);

    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }

    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);

    if (inet_aton(SERVER , &si_other.sin_addr) == 0) 
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    printf("Message : %d %d\n", *((int*)message), ((int*)message)[1] );

    //send the message
    if (sendto(s, message, BUFLEN , 0 , (struct sockaddr *) &si_other, slen)==-1)
    {
        die("sendto()");
    }

    close(s);
    return 0;
}
