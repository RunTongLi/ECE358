#include "networkqueue.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

NetworkQueue::NetworkQueue(int limit) : limit(limit) {}

bool NetworkQueue::push(Packet* p) {
    if (pkts.size() < limit) {
        pkts.emplace_back(p);
        return true;
    }
    return false;
}

void NetworkQueue::pop_until(double time) {
    int c = 0;
    /* if (pkts.size() > 0) { */
    /*     cout << ":" << pkts.front()->departure << " " << time; */
    /* } */
    while(pkts.size() > 0 && pkts.front()->departure < time) {
        pkts.pop_front();
        ++c;
    }
    /* cout << " " << c << " " << pkts.size() << endl; */ 
}

Packet* NetworkQueue::back() {
    return pkts.back();
}

Packet* NetworkQueue::front() {
    return pkts.front();
}

int NetworkQueue::size() {
    return pkts.size();
}

