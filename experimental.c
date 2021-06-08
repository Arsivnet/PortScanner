#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>


int main(void)
{

    struct addrinfo hints;
    struct addrinfo *res;
    int sockfd;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    char str[3] = "80";
    for(int i=0;i<200;i++)
    {
        
        sprintf(str, "%d", i);
        
        getaddrinfo("www.google.com", "443" , &hints, &res);

        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

        int c = connect(sockfd, res->ai_addr, res->ai_addrlen);

        if(c != -1)
        {
            printf("\n%d",i);
        }
        
    }


}