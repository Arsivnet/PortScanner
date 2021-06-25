#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define DOMAIN "www.google.com" //owner of the ports we're checking.
#define START 60 //start range of ports
#define END 110 //last port we're going to check

typedef struct arguments{

struct addrinfo *res; 

int sockfd;

int count;


} arguments;

int port_state[END - START];

void *ThreadingFun(void* arg){
	struct arguments *par = arg;
        //par.
	int c;
	printf("%d portu kontrol ediliyor %d\n ",par->count, pthread_self() );
	c = connect(par->sockfd, par->res->ai_addr, par->res->ai_addrlen);
	sleep(60);
	//while(c == 900)
	//{}
        if(c != -1)
        port_state[par->count - START] = 1;
	//printf("%d portu acik \n", par->i);
	else 
        port_state[par->count - START] = 2;
        //printf("%d portu kapali \n", par->i);
	pthread_exit(NULL);
}

void* run(void* arg){

}

int main(void)
{
    struct addrinfo hints; //hints basically determines which sockets get to be in res.
    struct addrinfo *res; //sockets we get from getaddrinfo, restricted by the attributes we specified in hints.
    int sockfd;
    pthread_t tid;
    struct arguments Parameters;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET; //We only want IPV4 sockets in res. So we specify this in hints. Use AF_INET6 for IPV6 and AF_UNSPEC for both.
    hints.ai_socktype = SOCK_STREAM;

    char service[4] = "80"; //Internet service and it's port number. 80 is arbitrary as we're using this variable to convert i to string. But you can type the number or the name of the service you want to check here and it will return the ports associated with that service. Number 80 is for HTTP.
    for(int i = START ;i < END ;i++)
    {

        sprintf(service, "%d", i);

        getaddrinfo(DOMAIN, service , &hints, &res);

	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	
	Parameters.res = res;
	Parameters.sockfd = sockfd;
	Parameters.count = i;

        pthread_create(&tid, NULL, ThreadingFun, &Parameters);
    }
    sleep(80);
for(int pcounter = START; pcounter< END; pcounter++){
printf(" port %d : %d \n", pcounter, port_state[pcounter-START]);
}

return 0;
}
