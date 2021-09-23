#ifndef PACKET_QUEUE_
#define PACKET_QUEUE_

#include <deque>
#include "packet.h"

class PacketQueue {
    std::deque<Packet*> pkts;
  public:
    void generatePackets(int A, double simTime);
    void updatePktArrivals(double waitTime);
    void push(Packet* p);
    void pop();
    Packet* front();
    int size();
};

#endif
