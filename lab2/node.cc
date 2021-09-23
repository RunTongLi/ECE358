#include "node.h"
#include <cmath>
#include <iostream>
#include <cassert>

using namespace std;

// Node constructor, generates all packets in queue
Node::Node(bool persistent, int A, int simTime) : persistent(persistent), collisionCount(0), busyCollisionCount(0) {
    pktqueue.generatePackets(A, simTime);
}

// Get number of packets left in queue
int Node::numPacketsLeft() {
    return pktqueue.size();
}

// Perform exponentialBackoff for collisions
void Node::exponentialBackoff() {
    ++collisionCount;
    if (collisionCount > 10) { // If we've reached 10 collisions remove packet
        removePacket();
        return;
    }

    // Generate wait time based on exponential backoff
    int max = (1 << busyCollisionCount) - 1;
    int R = max == 0 ? 0 : rand() % max;
    double wait = R*512/(double)1e6;
    double newTime = getNextPacket()->arrival + wait;
    pktqueue.updatePktArrivals(newTime);
}

// Handle packet waiting for busy channels
void Node::busyWait(double lower, double upper) {
    if (numPacketsLeft() == 0) return;
    Packet* p = getNextPacket();
    if (lower <= p->arrival && p->arrival < upper) {
        if (persistent) { // Persistent case, just set to when channel isn't busy
            pktqueue.updatePktArrivals(upper);
        } else {          // Non-persistent case, perform exponential backoff
            double newTime = p->arrival;
            while(newTime < upper) { // Keep checking until channel isn't busy
                ++busyCollisionCount;
                if (busyCollisionCount > 10) {
                    removePacket();
                    if (numPacketsLeft() == 0) return;
                    newTime = getNextPacket()->arrival;
                }
                // Generate wait time based on exponential backoff
                int max = (1 << busyCollisionCount) - 1;
                int R = max == 0 ? 0 : rand() % max;
                double wait = R*512/(double)1e6;
                newTime += wait;
            }
            pktqueue.updatePktArrivals(newTime);
        }
    }
}

// Get the next packet in queue
Packet* Node::getNextPacket() {
    return pktqueue.front();
}

// Remove the front packet in the queue
void Node::removePacket() {
    collisionCount = 0;
    busyCollisionCount = 0;
    pktqueue.pop();
}
