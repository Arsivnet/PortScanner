#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

#define DOMAIN "www.google.com" //owner of the ports we're checking.
#define START 0 //start range of ports
#define END 100 //last port we're going to check


int main(void)
{

    struct addrinfo hints; //hints basically determines which sockets get to be in res.
    struct addrinfo *res; //sockets we get from getaddrinfo, restricted by the attributes we specified in hints.
    int sockfd;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET; //We only want IPV4 sockets in res. So we specify this in hints. Use AF_INET6 for IPV6 and AF_UNSPEC for both.
    hints.ai_socktype = SOCK_STREAM;

    char service[4] = "80"; //Internet service and it's port number. 80 is arbitrary as we're using this variable to convert i to string. But you can type the number or the name of the service you want to check here and it will return the ports associated with that service. Number 80 is for HTTP.
    for(int i = START ;i < END ;i++)
    {

        sprintf(service, "%d", i);
    
        getaddrinfo(DOMAIN, service , &hints, &res);

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
