#include "channel.h"
#include <cmath>
#include <iostream>
#include <cstdlib>

using namespace std;

// Channel constructor, creates all nodes in channel
Channel::Channel(bool persistent, int N, int A, double t, double R, double D, double S) : t(t), R(R), D(D), S(S) {
    for (int i = 0; i < N; ++i) {
        nodes.emplace_back(new Node(persistent, A, t));
    }
}

// Channel destructor, deletes all nodes
Channel::~Channel() {
    for (size_t i = 0; i < nodes.size(); ++i) {
        delete nodes.at(i);
    }
}

// Returns whether there are nodes with more packets to send
bool Channel::finishedSimulating() {
    for (Node* node : nodes) {
        if (node->numPacketsLeft() > 0) {
            return false;
        }
    }
    return true;
}

// Runs a simulation of the system
void Channel::simulate(double& efficiency, double& throughput) {
    int transmissionCount = 0;
    int successCount = 0;
    double endTime = 0;

    while (!finishedSimulating() && endTime < t) {
        ++transmissionCount;
        int transmitIndex = getNextNode();
        Node* transmitNode = nodes.at(transmitIndex);
        Packet* transmitP = transmitNode->getNextPacket();
        double transmitDelay = transmitP->pktlen / R;

        vector<int> collidedPackets;
        double maxCollisionTime = 0;
        endTime = transmitP->arrival;

        // Check for collisions
        for (size_t i = 0; i < nodes.size(); ++i) {
            Node* node = nodes.at(i);
            if (node->numPacketsLeft() == 0) continue; // Node has no more packets to send
            Packet* p = node->getNextPacket();
            double propDelay = (abs((double)transmitIndex - i) * D) / S;
            if (i != transmitIndex && p->arrival <= transmitP->arrival + propDelay) {
                maxCollisionTime = max(maxCollisionTime, transmitP->arrival + propDelay);
                collidedPackets.emplace_back(i);
            }
        }

        if (collidedPackets.size() > 0) { // Observed a collision
            transmitNode->busyWait(transmitP->arrival, maxCollisionTime);
            transmitNode->exponentialBackoff();
            for (int i : collidedPackets) {
                ++transmissionCount;
                nodes.at(i)->exponentialBackoff();
            }
        } else { // Did not observe a collision
            ++successCount;
            transmitNode->removePacket();
            for (size_t i = 0; i < nodes.size(); ++i) {
                double propDelay = (abs((double)transmitIndex - i) * D) / S;
                nodes.at(i)->busyWait(transmitP->arrival + propDelay, transmitP->arrival + propDelay + transmitDelay);
            }
        }
    }

    // Calculate efficiency and throughput
    efficiency = (double) successCount / transmissionCount;
    throughput = ((double) successCount * 1500) / (R * endTime);
    cout << "E: " << efficiency << " T: " << throughput << endl;
}

// Returns the index of the node with the earliest packet arrival
int Channel::getNextNode() {
    int index = -1;
    double minArrival = -1;
    for (size_t i = 0; i < nodes.size(); ++i) {
        if (nodes.at(i)->numPacketsLeft() == 0) continue;
        if (minArrival == -1 || nodes.at(i)->getNextPacket()->arrival < minArrival) {
            minArrival = nodes.at(i)->getNextPacket()->arrival;
            index = i;
        }
    }
    return index;
}
