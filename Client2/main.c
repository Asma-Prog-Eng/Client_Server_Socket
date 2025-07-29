/* Create Client Socket ( the receiver)*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


// create a Socket for server communivation

short socketCreate(void) {


    short hSocket = 0;
    printf("Create the socket\n");
    hSocket = socket(AF_INET, SOCK_STREAM, 0);
    return hSocket;

}

// try to connect with server
int socketConnect(int hSocket) {

    int iRetval = -1;

    int ClientPort = 12346;

    struct sockaddr_in remote = {0};
    remote.sin_addr.s_addr = inet_addr("127.0.0.1"); //local Host
    remote.sin_family = AF_INET;
    remote.sin_port = htons(ClientPort);

    iRetval = connect(hSocket, (struct sockaddr *) &remote, sizeof(remote));

    return iRetval;

}


//receive the data from the server
int socketReceive(int hSocket, char* Rsp, short RvcSize) {

    int shortRetval = -1;
    struct timeval tv;
    tv.tv_sec = 20; /* 20 Secs Timeout */
    tv.tv_usec = 0;

    if (setsockopt(hSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv))< 0) {

        printf("Time Out\n");
        return -1;
    }

    shortRetval = recv(hSocket, Rsp, RvcSize, 0 );
    printf("Response %s\n", Rsp);

    return shortRetval;

}


int main(int argc, char *argv[])
{
    int hSocket = 0 , read_size = 0 ;
    char server_reply[200] = {0};

    //Create Socket
    hSocket = socketCreate();

    if (hSocket == -1) {

        printf("Could not create socket\n");
        return 1;

    }

    printf("Socket is created\n");
    // Connect to remote server
    if (socketConnect(hSocket) <0) {

        perror("connect failed.\n");
        return 1;
    }

    printf("Sucessfully connected with server\n");

    //Receive the data from the server
    read_size = socketReceive(hSocket, server_reply, 200);
    printf("Server Response : %s\n\n",server_reply);

    close(hSocket);


    return 0;
}
