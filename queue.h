#ifndef QUEUE
#define QUEUE

#include <stdbool.h>

typedef struct circular_queue circular_queue;
typedef circular_queue* messageQueue;

messageQueue init(char** messages, int size);

void freeQueue(messageQueue* mq);

void resetQueue(messageQueue* mq);

void addMessage(messageQueue mq, char[] message);


void char[] removeMessage(messageQueue mq, char[] message);

bool isEmpty(messageQueue mq);

bool isFull(messageQueue mq);

size_t capacity(messageQueue mq);

size_t size(messageQueue mq);

#endif
