#ifndef sharedResources
#define sharedResources

#include <stdbool.h>

typedef struct sharedResources sharedResources;
typedef sharedResources* ThreadShare;

void addSocket(ThreadShare ts, int socketID);

void removeSocket(ThreadShare ts, int socketID);

bool full(ThreadShare ts);

#endif
