#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

#include 'queue.h'

struct circular_queue{
  char** messageBuffer;
  size_t head, tail;
  size_t max;
  bool full;
};

static void advancePointer(circular_queue mq){
  mq->head = (mq->head + 1) % mq->max;
  mq->full = (mq->head == mq->tail);
}

static void retreatPointer(circular_queue mq){
  mq->tail = (mq->tail + 1) % mq->max;
  mq->full = false;
}

bool emptyMessageQueue(messageQueue mq){
  return (!mq->full && (mq->head == mq->tail));
}

bool fullMessageQueue(messageQueue mq){
  return mq->full;
}

messageQueue init(char** messages, size_t size){

  messageQueue mq = malloc(sizeof(circular_queue));

  mq->messageBuffer = messages;
  mq->max = size;

  resetQueue(mq);
  return mq;
}

void messageQueueFree(messageQueue mq){
  free(mq);
}

void messageQueueReset(messageQueue mq){
  mq->head = 0;
  mq->tail = 0;
  mq->full = false;
}

size_t messageQueueSize(messageQueue mq){
  size_t size = mq->size;

  if(!mq->full){
    if(mq->head >= mq->tail){
      size = (mq->head - mq->tail);
    }else{
      size = (mq->max + mq->head - mq->tail);
    }
  }
  return size;
}

void addMessageQueue(messageQueue mq, char *message){
  mq->messageBuffer[mq->head] = message;
  advancePointer(mq);
}

char* removeMessage(messageQueue mq, ){
  char* message;
  if(!){

  }
}
