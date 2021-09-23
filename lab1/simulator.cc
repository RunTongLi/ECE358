#include "simulator.h"
#include <vector>
#include <iostream>
#include "networkqueue.h"

using namespace std;

Simulator::Simulator(int T, int L, int C): T(T), L(L), C(C) {}

void Simulator::simulateQueue(const std::vector<Event*>& events, int k) {
    double currTime = 0;
    int obsCount = 0;
    NetworkQueue networkqueue = NetworkQueue(k);
    for (const auto& e : events) {
        switch(e->type) {
            case (Event::EventType::ARRIVAL):
                {
                    currTime = e->timestamp;
                    networkqueue.pop_until(currTime);
                    double servTime = e->pktlen / C;
                    Packet* p = new Packet(e->timestamp, e->pktlen);
                    if (networkqueue.size() == 0) {
                        p->departure = currTime + servTime;
                    } else {
                        p->departure = networkqueue.back()->departure + servTime;
                    }
                    if (!networkqueue.push(p)) {
                        p_loss += 1;
                    }
                    break;
                }
            case (Event::EventType::OBSERVE):
                currTime = e->timestamp;
                networkqueue.pop_until(currTime);
                e_n += networkqueue.size();
                if (networkqueue.size() == 0) {
                    p_idle += 1;
                }
                ++obsCount;
                break;
        }
    }
    e_n /= obsCount;
    p_idle /= obsCount;
};
