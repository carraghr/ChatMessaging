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

typedef struct shared_reader{
  int socketId;
  messageQueue mq;
}reader_args;

reader_args read_init(int socketID, messageQueue mq){
  reader_args reader = malloc(sizeof(shared_reader));
  reader->socketId = socketID;
  reader->mq = mq;
  return reader;
}

void read_updateID(int socketID, messageQueue mq){
  reader->socketId = socketID;
  return reader;
}

void *serverReaderThread(void *passedArgs){
  reader_args ra = (reader_args*)passedArgs;
  messageQueue mq = ra->mq;
  int socketID = ra->socketId;
  char buffer[1024] = {0};
  while((valread = read(socketID, buffer,1024))){
    addMessageQueue(mq,buffer);
  }
  removeSocket(socketID)
}

void *serverWriterThread(void *passedArgs){
  ThreadShare ts = (ThreadShare*)passedArgs;
  messageQueue mq = ts->mq;
  while(true){
    char* message = removeMessage(mq);
    int[] arr = getAllSockets();
    int length = sizeof(arr)/sizeof(int);
    for(int i=0; i<length;i++){
      send(arr[i], message, strlen(message), 0 );
    }
  }
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

    //create messageQueue
    char** buffer = malloc(BUFFERSIZE * sizeof(char*));
    messageQueue mq = message_queue_init(buffer, BUFFERSIZE);

    //create shared resources for threads to be created
    ThreadShare ts = thread_share_init(mq);

    bool work = true;
    pthread_t socket_write;
    pthread_create(&socketReaderThread,NULL,serverWriterThread,(void*)&ts);

    reader_args ra = read_init(0, mq);

    while(work){
      //listen for a client to approach the server
      if(listen(server_fd,3) < 0){
        perror("Socket Listening failed")
      }
      //accept a client socket
      if( (new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen)*&addrlen)) < 0){
        perror("accept");
        exit(EXIT_FAILURE);
      }else{
        addSocket(ts,new_socket);
        read_updateID(ra,new_socket);
        pthread_t socketReaderThread;
        signal(SIGINT,shutDownSignal);
        pthread_create(&socketReaderThread,NULL,serverReaderThread,(void*)&ra);
      }
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
