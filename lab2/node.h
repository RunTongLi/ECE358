#ifndef NODE_
#define NODE_

#include "packetqueue.h"

struct Packet;

class Node {
    bool persistent;
    PacketQueue pktqueue;
  public:
    int collisionCount;
    int busyCollisionCount;
    Node(bool persistent, int A, int simTime);
    int numPacketsLeft();
    void exponentialBackoff();
    void busyWait(double lower, double upper);
    Packet* getNextPacket();
    void removePacket();
};

#endif
