#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#define DOMAIN "www.google.com" //owner of the ports we're checking.
#define START 80 //start range of ports
#define END 81 //last port we're going to check


int main(void)
{

    struct addrinfo hints; //hints basically determines which sockets get to be in res.
    struct addrinfo *res; //sockets we get from getaddrinfo, restricted by the attributes we specified in hints.
    int sockfd, socket_flags;

    	int c = 1;
    //We want to send time to select() but we can't just specify seconds. We have to use timeval. So we defined two timevals, which can only be initialized with current time.
    //So we initialize two timevals and make the system wait the desired amount we want to wait for a port in between.
	struct timeval before;
	struct timeval after;
	gettimeofday(&before, NULL);
	sleep(2);
	gettimeofday(&after, NULL);
	after.tv_sec -= before.tv_sec; //Then we substract them from each other to get our desired time. defining a third timeval for it was unneccessary so we appointed it to after.
	after.tv_usec -= before.tv_usec;// Now after timeval after represents our desired time (two seconds)
    memset(&hints, 0, sizeof hints);

    hints.ai_family = AF_INET; //We only want IPV4 sockets in res. So we specify this in hints. Use AF_INET6 for IPV6 and AF_UNSPEC for both.
    hints.ai_socktype = SOCK_STREAM;

	fd_set wait_set; //We initialize our set. We will put all the ports here and then send it to select()
	FD_ZERO(&wait_set);
    char service[4] = "80"; //Internet service and it's port number. 80 is arbitrary as we're using this variable to convert i to string. But you can type the number or the name of the service you want to check here and it will return the ports associated with that service. Number 80 is for HTTP.
    for(int i = START ;i < END ;i++)
    {

        sprintf(service, "%d", i);
        getaddrinfo(DOMAIN, service , &hints, &res);
        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        printf("%d portu kontrol ediliyor\n ",i);
	socket_flags = fcntl(sockfd, F_GETFL, NULL); //we get the socket flags
	fcntl (sockfd, F_SETFL, socket_flags | O_NONBLOCK); //set the socket flags to be NONBLOCKING

	FD_SET(sockfd, &wait_set);
	/*else
	printf("%d Port açık \n ",i);
	fcntl(sockfd, F_SETFL, socket_flags);*/

}
	c = select(sockfd + 1, &wait_set, &wait_set, NULL, &after);
	printf("%d", &c);
        /*if(c < 0)
        {
        printf("%d Portu Kapalı \n ",i);
        }
	else if (c == 0)
		printf("Zaman asimina ugradi \n");
	else
            printf("%d Port açık \n ",i);*/
        return 0;
}

