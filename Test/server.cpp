//
// Created by hui on 16-11-22.
//
/**
 * This file is a test for tcp server using socket
 * visit    http://www.tuicool.com/articles/MfaI7bY
 *
 * step is:
 *      socket : declear a socket
 *      bind : bind Server IP and Port
 *      listen : set max listen number
 *      accept : using dead loop to wait client connect in.
 *      recv/send : always run in an independent thread to send or recv data with client.
 *      close: after done something close all socket.
 */

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
    int serverSocket;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int addr_len = sizeof(client_addr);
    int connectionSocket;
    char buffer[200];
    int iDataNum;

    /** create a socket for server
     *  doamain : AF_INET means ipv4
     *  type    : SOCK_STREAM , usually use with TCP
     *  protocol: IPPROTO_IP is Dummy protocol for TCP,会自动选择type类型对应的默认协议
     * */
    if((serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) < 0){
        perror("socket");
        return 1;
    }

    /** bind server socket with (IP, PORT) */
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;       // using ipv4
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(serverSocket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        perror("connect");
        return 1;
    }

    /** set the max listen number to 5 */
    if(listen(serverSocket, 5) < 0){
        perror("listen");
        return 1;
    }

    /** open a dead loop to wait client to connect in */
    while(1){
        printf("Listening on port: %d\n", SERVER_PORT);
        connectionSocket = accept(serverSocket, (struct sockaddr*)&client_addr, (socklen_t*)&addr_len);
        if(connectionSocket < 0){
            perror("accept");
            continue;
        }

        /** if connection had been set up, then recv or send data with client */
        printf("\nrecv data from %s:%d\n", inet_ntoa(client_addr.sin_addr), htons(client_addr.sin_port));
        while(1){
            iDataNum = (int)recv(connectionSocket, buffer, 1024, 0);
            if(iDataNum < 0){
                perror("receive");
                continue;
            }
            buffer[iDataNum] = '\0';
            if(strcmp(buffer, "over") == 0 || strcmp(buffer, "quit") == 0) {
                close(connectionSocket);
                break;
            }
            printf("recv %d bytes data is:\n%s\n", iDataNum, buffer);
            send(connectionSocket, buffer, (size_t)iDataNum, 0);
        }
        if(strcmp(buffer, "quit") == 0) {
            close(serverSocket);
            break;
        }
    }
    return 0;
}