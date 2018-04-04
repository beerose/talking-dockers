#include "utils.h"

#define MYPORT "54321"
#define MAXBUFLEN 100

int receivePackets();
int initSocket();
void *get_in_addr(struct sockaddr *sa);
