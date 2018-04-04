#include "receiver.h"
#include "sender.h"
#include "utils.h"

int main(int argc, char *argv[]) {
  if (strcmp(argv[1], "sender") == 0) {
    sendPackets();
  } else {
    receivePackets();
  }
}
