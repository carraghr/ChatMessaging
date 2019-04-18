#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080

typedef struct shared_reader{
  int socketId;
}args;

args args_init(int socketID){
  args arrs = malloc(sizeof(shared_reader));
  arrs->socketId = socketID;
  return arrs;
}

void *write_message_to_server(void *passedArgs){
  args ra = (args*)passedArgs;
  int sock = ra->socketId;
  char buffer[1024] = {0};

  while(true){
    scanf("%s", buffer);
    send(sock, buffer, strlen(buffer), 0);
  }
}

void *read_message_from_server(void *passedArgs){
  reader_args ra = (reader_args*)passedArgs;
  int socketID = ra->socketId;
  char buffer[1024] = {0};
  while((valread = read(socketID, serverMessageBuffer, 1024))>0){
      printf("%s\n",buffer );
  }
}

void shutDownSignal(int signalCode){
    if(signalCode == SIGINT){
        //put code to shut down threads and disconnet socket connection;
    }
}

int main(int argc, char const *argv[]){
  struct sockaddr_in address;
  int sock = 0, valread;
  struct sockaddr_in serverAddress;
  char buffer[1024] ={0};

  //create client socket
  if( (sock = socket(AF_INET, SOCK_STEAM, 0)) < 0){
    printf("\n Socket creation failed");
  }

  //create a copy of serverAddress with only the value of '0' for its size
  memset(&serverAddress, '0', sizeof(serverAddress));

  //assign socket server assess information ie IPv4 and port that it is available on

  serverAddress.sin_family = AF_INET;
  //The htons() function converts the unsigned short integer hostshort from host byte order to network byte order.
  serverAddress.sin_port = htons(PORT);

  //Convert Ip address from text to binary
  //inet_pton - convert IPv4 and IPv6 addresses from text to binary form
  if(inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0){
    printf("\n Invalid Address/ Address not supported \n");
    return -1;
  }

  //connect socket to server_fd
  if(connect(sock, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0){
    printf("\nConnection Failed\n");
    return -1;
  }

  args arrs = args_init(sock);

  signal(SIGINT,shutDownSignal);

  pthread_t write_thread;
  pthread_create(&write_thread,NULL,write_message_to_server,(void*)&arrs);

  pthread_t read_thread;
  pthread_create(&read_thread,NULL,read_message_from_server,(void*)&arrs);

  /***
  //to send message;
  send(sock, messageBuffer, strlen(messageBuffer), 0);

  //to recive message and display 1024 size of buffer
  valread = read(sock, serverMessageBuffer, 1024)
  */
  pthread_join(write_thread, NULL);

  pthread_join(read_thread, NULL);

  return 0;

}
