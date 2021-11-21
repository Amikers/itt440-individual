//server server
#include <netinet/in.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define MAX 1000
#define PORT 10162
#define SA struct sockaddr


//handle error by prompt exit
#define handle_error_en(en, msg) \
               do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)
#define handle_error(msg) \
               do { perror(msg); exit(EXIT_FAILURE); } while (0)
   
// Function designed for chat between client and server.
void func(int socket_desc)
{
	// get text
    char buff[MAX];
    int n;
      time_t seconds;
      
       for (;;) {
        bzero(buff, MAX);
    
    for (;;) {
        bzero(buff, MAX);

        // read the message from client and copy it in buffer
        read(socket_desc, buff, sizeof(buff));
        // print buffer which contains the client contents
        printf("Username is : %s\n", getlogin());
        //display result
        printf("Message from client: %s\t To client : ", buff);
        bzero(buff, MAX);
        
        
        // copy server message in the buffer
        while ((buff[n++] = getchar()) != '\n')
            ;
        // and send that buffer to client
        write(socket_desc, buff, sizeof(buff));
        printf("Send to client Time Protocol");
        //printf("Seconds since January 1, 1970 = %ld\n", seconds);
        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }

        }	
    }
	n = 0;
}
   
// Driver function connection 
int main()
{
    int socket_desc, connfd, len;
    struct sockaddr_in servaddr, cli;
   
    // socket create and verification
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
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
   
    // Binding  to given IP and verification
    if ((bind(socket_desc, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind error...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");
   
    //  server listen and verification
    if ((listen(socket_desc, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);
   
    // Accept the data packet from client and verification
    connfd = accept(socket_desc, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("server accept failed...\n");
        exit(0);
    }
    else
        printf("server accept the client...\n");
	    printf("This is ITT440 server...\n");
		printf("Waiting information from client...\n");
		
   
    // Function chat client server
    func(connfd);
   
    // socket close
    close(socket_desc);
}
