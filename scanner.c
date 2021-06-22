#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include <sys/socket.h>
#include <sys/types.h>

typedef struct 
{

    unsigned short int sa_family; //adres ailesi AF_x
    char sa_data[14]; //Protokol adresi ?

}socket_addr;



typedef struct 
{
    unsigned long int s_addr;
}in_addr;


typedef struct //Paketlenecek yapı
{
    short int          sin_family;  // Adres ailesi
    unsigned short int sin_port;    // Port numarası
    in_addr     sin_addr;    // Internet adresi
    unsigned char      sin_zero[8]; // struct sockaddr ile aynı boyda

}sockaddr_in;



int main(void)
{

    sockaddr_in addr;

    char ip[] = "216.58.214.142";
    int port = 23;
    int sockfd;
    
    
    /*
    "inet_addr"
    Taşınabilir sistemlerde kullanmak için daha mantıklı her sistemde inet_anot kullanılamıyormuş. -1 değeri ikili sayı sisteminde 255.255.255.255 kısmına denk geliyor ancak unsigned olarak
    atamışken nasıl -1 değerine sahip olacak ki?
    */

    addr.sin_family = AF_INET;         // konak bayt sıralaması
    addr.sin_port = htons(port);     // short, ağ bayt sıralaması
    addr.sin_addr.s_addr = inet_addr("216.58.214.142"); //Ağ bayt sıralamasına uygun olarak içeri koyuyor
    //inet_aton("216.58.214.142", &(my_addr.sin_addr)); Her sistemde çalışmayabilir inet_addr ile aynı işleve sahip sanırım
    memset(&(addr.sin_zero), '\0', 8); // geriye kalanı sıfırla 

    sockfd = socket(AF_INET,SOCK_STREAM,0);

    for(port = 0;port<9999;port++)
    {
        addr.sin_port = htons(port);
        int a = connect(sockfd, (socket_addr *)&addr, sizeof(socket_addr));
        if(a != -1)
        {
            printf("port %d \n",port);
        }
    }




}
