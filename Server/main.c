/* Create Server Socket */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


short socketCreate(void) {


    short hSocket = 0;
    printf("Create the socket\n");
    hSocket = socket(AF_INET, SOCK_STREAM, 0);
    return hSocket;

}

int bindCreateSocket(int hSocket) {

    int iRetval = -1;

    int ClientPort = 12346;

    struct sockaddr_in remote = {0};

    /* Internet address family */

    remote.sin_family = AF_INET;

    /* Any incoming interface*/

    remote.sin_addr.s_addr = htonl(INADDR_ANY);
    remote.sin_port = htons(ClientPort); // local port

    iRetval = bind(hSocket, (struct sockaddr *)&remote, sizeof(remote));

    return iRetval;

}


int main(int argc, char *argv[])
{
    int socket_desc = 0 , sock = 0, clientLen = 0;

    struct sockaddr_in client ;
    char client_message[200] = {0};
    char message[100] = {0};

    int x = 0;


    //Create socket

    socket_desc = socketCreate();
    if (socket_desc == -1)  {

        printf("Could not create socket");
        return 1;
    }


    printf("Socket created\n");

    // Bind
    if (bindCreateSocket(socket_desc) < 0 ) {

        //print the error message
        perror("bind failed.");
        return 1;

    }

    printf("bind done\n");

    //Listen , only two clients will wait
    listen(socket_desc, 2);

    printf("Waiting for incoming connections ...\n");
    clientLen = sizeof(struct sockaddr_in);

    //accept connection from an incoming client
    sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&clientLen);

    if (sock < 0 ) {

        perror("accept failed");
        return 1;

    }

    printf("Connection accepted\n");
    // initialize buffer for receiving and sending
    memset(client_message, '\0', sizeof(client_message));
    memset(message, '\0', sizeof(message));

    // Receive a reply from the client
    if ( recv(sock, client_message, 200, 0) < 0) {

        printf("recv failed");
    }

    printf("Received from Client : %s\n", client_message);

    x = atoi(client_message);

    x --;

    sprintf(message, "%d", x);

    // close socket for client 1
    close(sock);

    // wait for client 2

    printf("Waiting for incoming connections ...\n");

    // accept connection from an incoming client

    sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&clientLen);

    if ( sock <0) {

        perror("accept failed");
        return 1;
    }

    printf("Connection accepted\n");

    // send some data

    if (send(sock, message, strlen(message),0 ) < 0) {

        printf("Send failed");
        return 1;
    }


    close(sock);

    return 0;
}
