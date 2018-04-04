#include "sender.h"

SendInfo getSendInfo(const char *addr) {
  SendInfo info = {-1};
  int sockfd;
  struct addrinfo hints, *servinfo, *p;
  int rv;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;

  if ((rv = getaddrinfo(addr, SERVERPORT, &hints, &servinfo)) != 0) {
    std::cerr << "getaddrinfo: %s\n", gai_strerror(rv);
    return info;
  }

  for (p = servinfo; p != NULL; p = p->ai_next) {
    if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
      perror("socket");
      continue;
    }
    break;
  }

  if (p == NULL) {
    std::cerr << "failed to create socket\n";
    return info;
  }

  freeaddrinfo(servinfo);

  info.sockfd = sockfd;
  info.addr = p->ai_addr;
  info.len = p->ai_addrlen;
  return info;
}

void sendPacket(SendInfo info) {
  int numbytes;
  if ((numbytes = sendto(info.sockfd, "hello!", strlen("hello!"), 0, info.addr,
                         info.len)) == -1) {
    perror("sendto");
    return;
  }

  std::cout << "sent " << numbytes << "bytes to: " << RECEIVER_IP_ADDR << "\n";
}

int sendPackets() {
  int numbytes;

  SendInfo info = getSendInfo(RECEIVER_IP_ADDR);

  for (int i = 0; i < 5; i++) {
    sendPacket(info);
    sleep(1);
  }

  close(info.sockfd);
  return 0;
}
