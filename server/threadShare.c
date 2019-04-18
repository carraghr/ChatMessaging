#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include 'queue.h';
#include 'shared_resources.h'

#define SOCKETALLOWANCE 10

typedef struct sharedResources{
  int sockets[SOCKETALLOWANCE];
  int size;
  int input;
  messageQueue mq;
};

ThreadShare thread_share_init(messageQueue mq){

  ThreadShare ts = malloc(sizeof(sharedResources));

  ts->size = 0;
  ts->mq = mq;

  ts->input = 0;

  return ts;
}

void addSocket(ThreadShare ts, int socketID){
  int turn = 0;
  while(ts->sockets[ts->input] != -1 && turn != SOCKETALLOWANCE){
    turn++;
    ts->input = (ts->input+1)%SOCKETALLOWANCE;
  }
  if(turn == SOCKETALLOWANCE){
    return;
  }
  ts->sockets[ts->input] = socketID;
  ts->input = (ts->input +1) % SOCKETALLOWANCE;
  ts->size++;
}

void removeSocket(ThreadShare ts, int socketID){
    int turn = 0;
    while(ts->sockets[turn] != socketID && turn < SOCKETALLOWANCE){
      turn++;
    }
    if(turn == SOCKETALLOWANCE){
      return;
    }
    ts->sockets[turn] = -1;
    ts->size--;
}

bool full(ThreadShare ts){
  return (size == SOCKETALLOWANCE);
}

int[] getAllSockets(ThreadShare ts){
  int result[ts->size];
  for(int i = 0, index = 0; i<SOCKETALLOWANCE; i++){
    if(ts->sockets[i] != -1){
      result[index] = ts->sockets[i];
      index++;
    }
  }
  return result;
}
