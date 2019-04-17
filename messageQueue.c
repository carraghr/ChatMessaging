#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <semaphore.h>

#include 'queue.h'

struct circular_queue{
  char** messageBuffer;
  size_t head, tail;
  size_t max;
  bool full;
  sem_t mutex;
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

  sem_init(&mq->mutex,0,1);

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
  sem_wait(&mq->mutex);
  mq->messageBuffer[mq->head] = message;
  advancePointer(mq);
  sem_post(&mq->mutex);
}

char* removeMessage(messageQueue mq){
  char* message;
  sem_wait(&mq->mutex);
  while(emptyMessageQueue(mq)){
    sem_post(&mq->mutex);
    sem_wait(&mq->mutex);
  }
  message = mq->messageBuffer[mq->tail];
  retreatPointer(mq);
  sem_post(&mq->mutex);
  return message;
}
