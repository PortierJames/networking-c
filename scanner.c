#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
 
int main(int argc , char **argv)
{
    struct hostent *host;
    int i, sock, err;
    char hostname[127];
    struct sockaddr_in sa;
    
    printf("Enter website URL: ");
    gets(hostname);
 
    strncpy((char*)&sa, "", sizeof(sa));
    sa.sin_family = AF_INET;
     
    if(isdigit(hostname[0]))
    {
        printf("Doing lookup...");
        sa.sin_addr.s_addr = inet_addr(hostname);
        printf("Done\n");
    }
    else if ((host = gethostbyname(hostname)) != 0)
    {
        printf("Doing gethostbyname...");
        strncpy((char*)&sa.sin_addr, (char*)host->h_addr, sizeof sa.sin_addr);
        printf("Done\n");
    }
    else
    {
        herror(hostname);
        exit(2);
    }
     
    printf("Starting the portscan loop : \n");
    for (i = 20; i <= 1023; i++) 
    {
        sa.sin_port = htons(i);
        
        sock = socket(AF_INET , SOCK_STREAM , 0);
        if(sock < 0) 
        {
            perror("\nSocket");
            exit(1);
        }
        
        err = connect(sock, (struct sockaddr*)&sa, sizeof sa);
        if(err < 0)
        {
            //printf("%s %-5d %s\r", hostname, i, strerror(errno));
            fflush(stdout);
        }
        else
        {
            printf("PORT %-5d is OPEN\n",  i);
        }
        close(sock);
    }
     
    printf("\r");
    fflush(stdout);
    return(0);
} 
