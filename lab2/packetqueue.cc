#include "packetqueue.h"
#include <math.h>
#include <time.h>
#include <iostream>

using namespace std;

// Generates random values following poisson distribution
double generateExp(double lambda) {
    double u = (double) rand() / RAND_MAX;
    return -(1/lambda)*log(1-u);
}

// Generate all packets for a node
void PacketQueue::generatePackets(int A, double simTime) {
    double time = 0;
    while (time < simTime) {
        time += generateExp(A);
        push(new Packet(time));
    }
}

// Update packet arrivals in the packet queue so all packets arrive after or at newTime
void PacketQueue::updatePktArrivals(double newTime) {
    if (pkts.size() == 0) return;
    for (auto& pkt : pkts) {
        if (pkt->arrival <= newTime) {
            pkt->arrival = newTime;
        } else {
            break;
        }
    }
}

// Push packet on to queue
void PacketQueue::push(Packet* p) {
    pkts.emplace_back(p);
}

// Pop packet off of queue
void PacketQueue::pop() {
    pkts.pop_front();
}

// Get first packet on the queue
Packet* PacketQueue::front() {
    return pkts.front();
}

// Get size of packet queue
int PacketQueue::size() {
    return pkts.size();
}
