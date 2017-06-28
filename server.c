#include "zconf.h"
#include "strings.h"
#include "arpa/inet.h"
#include "stdlib.h"
#include "stdio.h"

#define MAXLINE 4096
#define SA struct sockaddr

int main(int argc, char **argv) {
    int     sockfd, connfd;
    socklen_t clilen;
    char    buff[MAXLINE];
    struct  sockaddr_in servaddr, cliaddr;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("create sockfd failed!");
        exit(0);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0) {
        printf("bind sockfd failed!");
        exit(0);
    }

    if(listen(sockfd, 1024) < 0){
        printf("listen sockfd failed!");
        exit(0);
    }

    for( ; ; ) {
        clilen = sizeof(cliaddr);
        connfd = accept(sockfd, (SA *) &cliaddr, &clilen);

        snprintf(buff, sizeof(buff), "%.24s\r\n", "This Is Mario");
        write(connfd, buff, strlen(buff));
        close(connfd);
    }
}
