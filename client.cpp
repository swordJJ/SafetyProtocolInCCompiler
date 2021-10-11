//
// Created by hui on 16-11-22.
//

/**
 * This is a test file for TCP Client using socket
 * visit    http://www.tuicool.com/articles/MfaI7bY
 *
 * steps:
 *      socket : create a cleint socket
 *      connect : connect to server socket
 *      recv/send : excahnge data with server in a dead loop
 *      clsoe: close socket
*/

/*socket tcp客户端*/
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SERVER_PORT 10000

int main(){
    int clientSocket;
    struct sockaddr_in server_addr;
    char sendbuf[200];
    char recvbuf[200];
    int iDataNum;
    if((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(connect(clientSocket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        perror("connect");
        return 1;
    }

    printf("connect with destination host...\n");
    while(1){
        printf("Input your world:>");
        scanf("%s", sendbuf);                   // read a word, space or \n to end input
        printf("\n");

        send(clientSocket, sendbuf, strlen(sendbuf), 0);
        if(strcmp(sendbuf, "quit") == 0) break;
        iDataNum = (int)recv(clientSocket, recvbuf, 200, 0);
        recvbuf[iDataNum] = '\0';
        printf("recv data of my world is: %s\n", recvbuf);
    }
    close(clientSocket);
    return 0;
}