#include "utils.h"

#define SERVERPORT "54321"

typedef struct {
  int sockfd;
  sockaddr *addr;
  socklen_t len;
} SendInfo;

SendInfo getSendInfo(const char *addr);
int sendPackets();
