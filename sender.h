#include "utils.h"

typedef struct {
  int sockfd;
  sockaddr *addr;
  socklen_t len;
} SendInfo;

SendInfo getSendInfo(const char *addr);
int sendPackets();
