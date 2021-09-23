#ifndef NETWORK_QUEUE_
#define NETWORK_QUEUE_

#include <deque>
#include "packet.h"

class NetworkQueue {
    int limit;
    std::deque<Packet*> pkts;
  public:
    NetworkQueue(int limit);
    bool push(Packet* p);
    void pop_until(double time);
    Packet* back();
    Packet* front();
    int size();
};

#endif
