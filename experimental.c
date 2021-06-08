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

    char str[4] = "80";
    for(int i=0;i<200;i++)
    {
        
        sprintf(str, "%d", i);
    
        getaddrinfo("www.google.com", str , &hints, &res);

        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        printf("%d portu kontrol ediliyor\n ",i);
        int c = connect(sockfd, res->ai_addr, res->ai_addrlen);

        if(c != -1)
        {
            printf("%d Port açık \n ",i);
        }
        else printf("%d Portu Kapalı \n ",i);
        
    }


}