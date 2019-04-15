#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#include 'queue.h'

#define PORT 8080
#define BUFFERSIZE 10

typedef struct sharedResources{
  int sockets[10];
  int size;
  circular_queue mq;

}ThreadShare;

void *serverReaderThread(void *passesSocket){
}


int main(int argc, char const *argv[]){
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen= sizeof(address);
    char buffer[1024] = {0};
    char *message;



    //create socket for server
    if( (server_fd = socket(AF_INET, SOCK_STEAM, 0)) == 0 ){
        perror("Socket Creation Failed!");
        exit(EXIT_FAILURE);
    }

    // Connect socket to the port 8080
    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &opt,sizeof(opt))){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr =  INADDR_ANY;
    address.sin_port = htons(PORT);

    //Bind socket to the port 8080
    if(bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0 ){
      perror("Socket Binding Failed");
      exit(EXIT_FAILURE);
    }


    //create shared resources for threads to be created
    ThreadShare share;


    //create messageQueue
    char** buffer = malloc(BUFFERSIZE * sizeof(char*));
    circular_queue mq = init(buffer, BUFFERSIZE);

    bool work = true;

    while(work){
      //listen for a client to approach the server
      if(listen(server_fd,3) < 0){
        perror("Socket Listening failed")
      }
      //accept a client socket
      if( (new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen)*&addrlen)) < 0){
        perror("accept");
        exit(EXIT_FAILURE);
      }

      pthread_t socketReaderThread;
      signal(SIGINT,shutDownSignal);
      pthread_create(&socketReaderThread,NULL,serverReaderThread,(void*)&);

    }

    //accept a client socket
    /***
    if( (new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen)*&addrlen)) < 0){
      perror("accept");
      exit(EXIT_FAILURE);
    }

    //here the program will pass wait for the
    valread = read(new_socket,buffer,1024)

    realisty I should have a while loop that loops the accepting of sockets
    adds vaild sockets to a list and creates a pthread for waiting for reads.
    a bounded buffer is going to be needed.
    a list of sockets is also going to be needed.
    pthreads for each socket, and one main one for the message buffer.
    */

}
