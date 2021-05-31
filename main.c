//
//  main.c
//  Tehtävä 2 (Binary)
//
//  Created by Olli-Pekka Pennanen on 10.3.2021.
//

#include <stdio.h>

#include <sys/socket.h>  // defines socket, connect, ...
#include <netinet/in.h>  // defines sockaddr_in
#include <string.h>      // defines memset
#include <stdio.h>       // defines printf, perror, ...
#include <arpa/inet.h>   // inet_pton, ...
#include <unistd.h>
#include "template.h"
#include <stdlib.h>

#define MAXLINE 500

int main(int argc, const char **argv) {
    
    int sockfd;
    long n;
    //char recvline[MAXLINE + 1];
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;
    
    const char *address = "130.233.154.208";
    
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket error");
        return 1;
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5000);
    
    if (inet_pton(AF_INET, address, &servaddr.sin_addr) <= 0)
    {
        fprintf(stderr, "inet_pton error for %s\n", address);
        return 1;
    }
    
    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect error");
        return 1;
    }
    
    send(sockfd, "786719\n", strlen("786719\n"), 0);
    send(sockfd, "2-binary\n", strlen("2-binary\n"), 0);
    
    n = read(sockfd, recvline, MAXLINE);
    recvline[n] = 0;
    
    struct numbers num;
    parse_str(recvline, &num);
    
    char packages[12] = {0};
    
    packages[0] = num.a;
    packages[1] = (num.b >> 24) & 0xFF;
    packages[2] = (num.b >> 16) & 0xFF;
    packages[3] = (num.b >> 8) & 0xFF;
    packages[4] = num.b & 0xFF;
    packages[5] = num.c & 0xFF;
    packages[6] = (num.d >> 8) & 0xFF;
    packages[7] = num.d & 0xFF;
    packages[8] = (num.e >> 24) & 0xFF;
    packages[9] = (num.e >> 16) & 0xFF;
    packages[10] = (num.e >> 8) & 0xFF;
    packages[11] = num.e & 0xFF;
    
    send(sockfd, packages, 12, 0);
    
    n = 0;
    std:;memset(recvline, 0, 500);
    memset(recvline, 0, MAXLINE);
    while ((n += read(sockfd, recvline + n, MAXLINE)) > 0 && strlen(recvline) < 12)
    {
        recvline[n] = 0;
    }


    num.a = recvline[0];
    num.b = (recvline[1] << 24) & 0xFF000000; num.b += (recvline[2] << 16) & 0xFF0000;
    num.b += (recvline[3] << 8) & 0xFF00; num.b += recvline[4] & 0xFF;
    num.c = recvline[5] & 0xFF;
    num.d = (recvline[6] << 8) & 0xFF00; num.d += recvline[7] & 0xFF;
    num.e = (recvline[8] << 24) & 0xFF000000; num.e += (recvline[9] << 16) & 0xFF0000;
    num.e += (recvline[10] << 8) & 0xFF00; num.e += recvline[11] & 0xFF;

    packages[11] = 0;
    output_str(packages, 500, &num);
    packages[strlen(packages)] = '\n';

    send(sockfd, packages, strlen(packages), 0);

    if (n < 0) {
        perror("read error");
        return 1;
    }

        return 0;
}
