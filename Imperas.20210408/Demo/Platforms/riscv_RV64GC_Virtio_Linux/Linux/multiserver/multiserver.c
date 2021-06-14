/*
 Demo of client-server application, like GDB RSP,
 with a second socket giving async communication
 back to the client without disturbing the RSP semantics. */

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


typedef unsigned int Uns32;
typedef signed int   Int32;
typedef int          Bool;

#ifdef _WIN32
#include "windows.h"
#include <time.h>
#include <sys/time.h>

static void _winWaitForTime(LARGE_INTEGER liDueTime)
{
    HANDLE hTimer = CreateWaitableTimer(NULL, TRUE, "WaitableTimer");
    SetWaitableTimer(hTimer, &liDueTime, 0, NULL, NULL, 0);

    WaitForSingleObject(hTimer, INFINITE);

    CloseHandle(hTimer);
}

unsigned int USleep(unsigned long usec)
{
    LARGE_INTEGER liDueTime;
    liDueTime.QuadPart = (long) (0-(usec * 10));
    _winWaitForTime(liDueTime);
    return 0;
}

void socketInit(void) {
    static int done = 0;
    if ( !done ) {
        done = 1;
        WSADATA info;
        if ( WSAStartup(MAKEWORD(2,2), &info) != 0 ) {
            printf( "Error initializing Windows networking");
            exit(1);
        }
    }
}

int socketClose(int fd) {
    return closesocket(fd);
}

#else

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <unistd.h>

unsigned int USleep(unsigned long usec) {
    return usleep(usec);
}

void socketInit(void) {
}

int socketClose(int fd) {
    return close(fd);
}

#endif


#define MAX_CLIENTS   10
#define LOOPS         100
#define LOOP_SLEEP_US 0
#define MAX_PACKET    1024

typedef struct serverStrS {
    int fd;
    int open;
} serverStr, *serverStrP;

serverStr clientSockets[MAX_CLIENTS];

//
// Find  an entry that is not being used
//
static int findFreeEntry() {
    int i;
    for(i = 0; i < MAX_CLIENTS; i++) {
        if (clientSockets[i].open == 0) {
            return i;
        }
    }
    printf( "No free sockets\n");
    exit(1);
    return 0;
}

//
// Needed by select
//
static int findMaxFD(int serverSocket) {
    int i;
    int max = serverSocket;
    for(i = 0; i < MAX_CLIENTS; i++) {
        if (clientSockets[i].open) {
            if (clientSockets[i].fd > max) {
                max = clientSockets[i].fd;
            }
        }
    }
    return max;
}

//
// Start listening on the given port number
//
static int startServerOnPort(int portNumber) {
    Bool allowRemote = 1;
    struct sockaddr_in socketAddress;
    int serverSocket;
#if(_WIN32==1)
    Int32 structLen;
#else
    Uns32 structLen;
#endif

    socketInit();

    // Create listening socket waiting for 'remote' connection from gdb
    if ( (serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1 ) {
        printf( "Failed to create server socket\n");
        exit(1);
    }
    //int flags = fcntl(serverSocket, F_GETFL, 0);

    //if (fcntl(serverSocket, F_SETFL, flags| O_NONBLOCK) <0) {
    //    printf( "fcntl SETFL failed\n");
    //    exit(1);
    //}

    memset(&socketAddress, 0, sizeof(socketAddress));
    socketAddress.sin_family = AF_INET;
    socketAddress.sin_addr.s_addr = htonl(allowRemote ? INADDR_ANY : INADDR_LOOPBACK);
    socketAddress.sin_port = htons(portNumber);

    if ( bind(serverSocket, (struct sockaddr *) &socketAddress, sizeof(socketAddress)) != 0 ) {
        printf( "Failed to bind server socket on %d : %s\n", portNumber, strerror(errno));
        exit(1);
    }

    if ( listen(serverSocket, 1) != 0 ) {
        printf(  "Failed to listen on server socket\n");
        exit(1);
    }

    structLen = sizeof(socketAddress);
    memset(&socketAddress, 0, sizeof(socketAddress));
    if ( getsockname(serverSocket, (struct sockaddr *) &socketAddress, &structLen) != 0 ) {
        printf(  "Failed to get server socket information\n");
        exit(1);
    }

    Uns32 listenPort = ntohs(socketAddress.sin_port);
    const char *listenAddress = inet_ntoa(socketAddress.sin_addr);
    printf( "Server listening on %s:%u\n", listenAddress, listenPort);

    // show that we are waiting for connection
    char buff[MAX_PACKET];
    const char *host = gethostname(buff, sizeof(buff)) ? buff : listenAddress;
    printf(  "Host: %s, Port: %d  waiting for client to connect\n", host, listenPort);

    structLen = sizeof(socketAddress);
    memset(&socketAddress, 0, sizeof(socketAddress));

    return serverSocket;
}

//
// A message has arrived. Send a response
//
static void processMessage(serverStrP str) {
    char rx[MAX_PACKET];
    int fd = str->fd;
    int r = recv(fd, rx, MAX_PACKET, 0);
    if(r > 0) {
        rx[r] = 0;
        printf( "    read %d bytes  [%s]\n", r, rx);

        char reply[MAX_PACKET+16];
        snprintf(reply, sizeof(reply), "Answer to [%s]", rx);

        r = send(fd, reply, strlen(reply), 0);
        printf( "    sent %d bytes  [%s]\n", r, reply);
    } else if (r < 0) {
        printf( "socket error %s\n", strerror(errno));
        exit(1);
    } else {
        printf( "client disconnected\n");
        socketClose(fd);
        str->open = 0;
        str->fd = -1;
    }
}

//
// Set the select bits. One bit is set for the listening socket,
// and one for each open connection.
//
static void setSet(fd_set *set, Uns32 serverSocket) {
    FD_ZERO(set);
    FD_SET(serverSocket, set);
    int i;
    for (i = 0; i < MAX_CLIENTS; i++) {
        if(clientSockets[i].open) {
            FD_SET(clientSockets[i].fd, set);
        }
    }
}

void getSocketData(int serverSocket, fd_set *read_fds) {
    // select says at least one socket is ready
    if (FD_ISSET(serverSocket, read_fds)) {
        // The listening socket has got a new client
        int entry = findFreeEntry();
        if(entry >= 0) {
            int skt = accept(serverSocket, NULL, NULL);
            printf( "connection accepted on fd %d\n", skt);
            int flag = 1;
            if ( setsockopt(skt,IPPROTO_TCP, TCP_NODELAY,(char*) &flag, sizeof(flag)) != 0) {
                 printf( "Failed to set NODELAY socket option for GDB RSP connection\n");
                 exit(1);
            }
            clientSockets[entry].fd   = skt;
            clientSockets[entry].open = 1;
        } else {
            printf( "No sockets available\n");
            exit(1);
        }
    }
    // check the status of the other sockets
    int i;
    for(i= 0; i < MAX_CLIENTS; i++) {
        if (clientSockets[i].open && FD_ISSET(clientSockets[i].fd, read_fds)) {

            // An existing connection has received a packet
            processMessage(&clientSockets[i]);
        }
    }
}
//
// Listen on the server socket and on any open connections
//
void serviceSockets(int serverSocket) {

    fd_set read_fds;

    setSet(&read_fds, serverSocket);
    int max = findMaxFD(serverSocket);
    int s   = select(max+1, &read_fds, NULL, NULL, NULL);

    if(s > 0) {
        getSocketData(serverSocket, &read_fds);
    }
}

//
// The server. Start listening on the given port, continue listening for new connections
// while responding to messages from existing connections.
//
void server(Uns32 portNumber, const char *hostname) {
    int serverSocket = startServerOnPort(portNumber);
    while(1) {;
        serviceSockets(serverSocket);
    }
}


//////////////////////////////////////// CLIENT //////////////////////////////////////////////

//
// The client is a standard TCP client program
// It connects to a given host and port number, then sends <LOOPS> packets and reports the
// reponses, before exiting
//


//
// Connect a TCP socket to the given host and port
//
int startClient(Uns32 port, const char *hostname) {

    socketInit();

    Int32 clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket < 0) {
        printf( "Failed to create a socket for RSP connection\n");
        exit(1);
    }

    printf( "Client starting\n");

    // Get the address of the server
    struct hostent *server = gethostbyname(hostname);
    if(!server) {
        printf( "No such host '%s'\n", hostname);
        exit(1);
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port   = htons(port);
    memcpy(&serverAddr.sin_addr.s_addr, server->h_addr, server->h_length);

    // Loop on connect in case the clients starts before the server

    while (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("Failed to connect fd:%d to %s:%d    %s\n",
           clientSocket,
           hostname,
           port,
           strerror(errno)
        );
        fflush(0);
        USleep(1000000);
    }
    printf( "Client connected to fd:%d  %s:%d\n", clientSocket, hostname, port);

    int flag = 1;
    if ( setsockopt(clientSocket, IPPROTO_TCP, TCP_NODELAY, (char*) &flag, sizeof(flag)) != 0) {
        printf(  "Failed to set NODELAY socket option for RSP connection\n");
    }

    return clientSocket;
}

void clientGetResponse(int clientFd, const char *hostname){
    int r;
    int response = 0;
    char ack[MAX_PACKET];
    do {
        // receive an answer
        do {
            r = recv(clientFd, ack, sizeof(ack), 0);
        } while(r < 0 && errno == EINTR);

        if (r == 0) {
            printf( "shutdown from server\n");
            exit(0);
        } else if (r < 0) {
            printf( "socket error %s\n", strerror(errno));
        }

        ack[r] = 0;
        if(strncmp(ack,"Answer",6) == 0) {
            printf( "    client response message received\n");
            response = 1;
        } else {
            printf( "    client unexpected message ignored\n");
        }
    } while(!response);

    printf( "    %s received [%s]\n", hostname, ack);

}

int clientSendMessage(int clientFd, const char *hostname, int number){
    int r;

    // construct an interesting packet to send to the server
    char sendBuffer[128];
    snprintf(sendBuffer, sizeof(sendBuffer), "%s:%d", hostname, number);

    // send the packet
    printf( "    client %s sending [%s]\n", hostname, sendBuffer);
    do {
        r = send(clientFd, sendBuffer,strlen(sendBuffer) , 0);
    } while(r < 0 && errno == EINTR);

    return r;
}

void client (Uns32 port, const char *hostname) {

    int clientFd = startClient(port, hostname);

    int i;
    for(i= 0; i < LOOPS; i++) {
        int r;

        r = clientSendMessage(clientFd, hostname, i);

        if (r == 0) {
            printf( "shutdown from server\n");
            exit(0);
        } else if (r < 0) {
            printf( "socket error %s\n", strerror(errno));
            // do it again?
            i--;
            continue;
        }

        clientGetResponse(clientFd, hostname);

        // wait so we can watch it happening in real time
        USleep(LOOP_SLEEP_US);
    }
    printf( "%s Done\n", hostname);
}


///////////////////////////////////////// MAIN ///////////////////////////////////////////////


static void usage(const char *exe) {
    printf(  "Usage %s c|s <port> [host]\n\n", exe);
    exit(1);
}

//
// This program can be the client or the server
//
int main(int argc, const char *argv[]) {
    if (argc != 4 && argc != 3) {
        usage(argv[0]);
    }
    int port         = atoi(argv[2]);
    const char *host =  argv[3] ?: "127.0.0.1";

    if (argv[1][0] == 'c') {
        printf("Client\n");
        fflush(0);
        client(port, host);
    } else if (argv[1][0] == 's' ){
        printf( "Server\n");
        server(port, host);
    } else {
        usage(argv[0]);
    }
    return 0;
}
