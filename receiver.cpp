#include "receiver.h"

int initSocket() {
  int sockfd;
  struct addrinfo hints, *servinfo, *p;
  int rv;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = AI_PASSIVE; // use my IP

  if ((rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo)) != 0) {
    std::cout << "getaddrinfo: " << gai_strerror(rv) << "\n";
    return 1;
  }

  // loop through all the results and bind to the first that is ok
  for (p = servinfo; p != NULL; p = p->ai_next) {
    if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
      perror("listener: socket");
      continue;
    }

    if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
      close(sockfd);
      perror("listener: bind");
      continue;
    }

    break;
  }

  if (p == NULL) {
    fprintf(stderr, "listener: failed to bind socket\n");
    return -1;
  }

  freeaddrinfo(servinfo);
  return sockfd;
}

int receivePackets() {
  int numbytes;
  char buf[MAXBUFLEN];

  int sockfd = initSocket();

  struct sockaddr_storage their_addr;
  socklen_t addr_len = sizeof their_addr;
  if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN - 1, 0,
                           (struct sockaddr *)&their_addr, &addr_len)) == -1) {
    perror("recvfrom");
    return -1;
  }

  std::cout << "packet contains: " << buf << "\n";

  close(sockfd);

  return 0;
}
