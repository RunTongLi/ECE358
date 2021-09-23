#ifndef CHANNEL_
#define CHANNEL_

#include <vector>
#include "node.h"

class Channel {
    std::vector<Node*> nodes;
    double t;
    double R;
    double D;
    double S;
    int getNextNode();
    bool finishedSimulating();
  public:
    Channel(bool persistent, int N, int A, double t, double R, double D, double S);
    ~Channel();
    void simulate(double& efficiency, double& throughput);
};

#endif
