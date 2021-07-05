#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#define DOMAIN "www.archlinux.org" //owner of the ports we're checking. This could be IP like 192.0.2.33 or domain name like "www.artixlinux.org".
#define START 78 //start range of ports
#define END 85 //last port we're going to check
#define TIMEOUT 1 //amount of seconds you want to wait before giving up on a connection.

int main(void)
{

    struct addrinfo hints; //hints basically determines which sockets get to be in res.
    struct addrinfo *res; //sockets we get from getaddrinfo, restricted by the attributes we specified in hints.
    int sockfd;

	int error_code;
	int error_code_size = sizeof(error_code); //We're using asynch connection. So we initialize an error_code to check if a connection is up. Had we used synch connection, we could simply get the output of our connect() function to check if it was successful.

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET; //We only want IPV4 sockets in res. So we specify this in hints. Use AF_INET6 for IPV6 and AF_UNSPEC for both.
    hints.ai_socktype = SOCK_STREAM;
    char service[4] = "80"; //Internet service and it's port number. 80 is arbitrary as we're using this variable to convert i to string. But you can type the number or the name of the service you want to check here and it will return the ports associated with that service. Number 80 is for HTTP.
    for(int i = START ;i < END ;i++)
    {

        sprintf(service, "%d", i);
    
        getaddrinfo(DOMAIN, service , &hints, &res);

        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	fcntl(sockfd, F_SETFL, O_NONBLOCK); //We set the socket to be non-blocking. this will shorten connection time. When a socket is blocking, it will hold the program until a response is given. This makes the program waste time on closed ports because they won't respond. But now we won't be able to tell if we connected through int C because a non-blocking socket doesn't wait for the output of connect().
        printf("%d portu kontrol ediliyor\n ",i);
        int c = connect(sockfd, res->ai_addr, res->ai_addrlen);
	sleep(TIMEOUT); //This is the timeout. We wait for 1 sec for the connection. WARNING: This value is too low for some addresses like www.Google.com
	getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error_code, &error_code_size);
        //printf("%d\n", error_code);
	if(error_code != 0)
        {
            printf("%d Portu kapali \n ",i);
        }
        else printf("%d Portu acik \n ",i);
        
    }

    return 0;
}
