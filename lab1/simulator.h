#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <vector>
#include "event.h"

class Simulator {
  public:
    int T;
    int L;
    int C;
    double e_n;
    double p_idle;
    double p_loss;
    Simulator(int T, int L, int C);
    void simulateQueue(const std::vector<Event*>& events, int k);
};

#endif
