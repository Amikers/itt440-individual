//client client
#include <netdb.h>
#include <stdio.h>
#include <unistd.h> //write
#include <stdlib.h>
#include <arpa/inet.h> //inet_addr
#include <string.h>
#include <time.h> //for time

#define MAX 1000
#define PORT 10162
#define SA struct sockaddr

//handle error by prompt exit
#define handle_error_en(en, msg) \
               do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)
#define handle_error(msg) \
               do { perror(msg); exit(EXIT_FAILURE); } while (0)

void func(int socket_desc)
{
    char buff[MAX];
    int n;
    time_t seconds;

        for (;;) {
        bzero(buff, MAX);
    //chat between client and server
    for (;;) {
        bzero(buff, sizeof(buff));
        seconds = time(NULL);
        printf("Enter the information : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n');
        write(socket_desc, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(socket_desc, buff, sizeof(buff));

        printf("From Server : %s", buff);
        

        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }

        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
        //to get time for protocol
        printf("Seconds since January 1, 1970 = %ld\n", seconds);

    }

        }
}

int main()
{
    int socket_desc, connfd;
    struct sockaddr_in servaddr, cli;

    // socket create and varification
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("socket failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("192.168.56.107");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(socket_desc, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    // function for chat
    func(socket_desc);

    // close the socket
    close(socket_desc);
}



