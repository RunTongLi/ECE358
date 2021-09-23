#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <unistd.h>
#include "networkqueue.h"
#include "packet.h"
#include "event.h"
#include "simulator.h"
#include "csvwriter.h"

using namespace std;

double generateExp(double lambda) {
    double u = (double) rand() / RAND_MAX;
    return -(1/lambda)*log(1-u);
}

void generateArrivals(vector<Event*>& v, double lambda, double L, double T) {
    double time = 0;
    while (time < T) {
        time += generateExp(lambda);
        double len = generateExp(1/L);
        v.emplace_back(new Event(Event::EventType::ARRIVAL, time, len));
    }
}

void generateObs(vector<Event*>& v, double lambda, double T) {
    double time = 0;
    while(time < T) {
        time += generateExp(5*lambda);
        v.emplace_back(new Event(Event::EventType::OBSERVE, time, 0));
    }
}

double getAvg(const vector<double>& dis) {
    double avg = 0;
    for (auto& v : dis) {
        avg += v;
    }
    return avg / dis.size();
}

double getVariance(const vector<double>& dis) {
    double avg = getAvg(dis);
    double var = 0;
    for (auto& v : dis) {
        var += pow(v - avg, 2);
    }
    return var / dis.size();
}

void verifyDistr() {
    double lambda = 75;
    vector<double> dis(1000);
    for (auto& v : dis) {
        v = generateExp(lambda);
    }
    double avg = getAvg(dis);
    double var = getVariance(dis);
  	cout << "REAL AVG: " << avg;
	cout << " EXPECTED AVG: " << 1.0/lambda << endl;
	cout << "VAR: " << var;
	cout << " EXPECTED VAR: " << 1.0/pow(lambda, 2) << endl;
}

bool cmpEvent(Event* a, Event* b) {
    return *a < *b;
}

void simulateQ3() {
    int T = 2000;
    int L = 2000;
    int C = 1000000;
    vector<vector<double>> p_idle;
    vector<vector<double>> e_n;
    CSVWriter writer;
    for (double rho = 0.25; rho <= 0.95; rho += 0.1) {
        Simulator sim = Simulator(T, L, C);
        double lambda = rho*C/L;
        vector<Event*> events;
        generateArrivals(events, lambda, L, T);
        generateObs(events, lambda, T);
        sort(events.begin(), events.end(), cmpEvent);

        sim.simulateQueue(events, INT16_MAX);
        p_idle.emplace_back(vector<double>{sim.p_idle, rho});
        e_n.emplace_back(vector<double>{sim.e_n, rho});
        cout << "E[n]: " << sim.e_n << endl;
        cout << "P_idle: " << sim.p_idle << endl;
        cout << endl;
    }
    writer.writecsv(e_n, "q3e_n.csv");
    writer.writecsv(p_idle, "q3p_idle.csv");
}

void simulateQ4() {
    int T = 2000;
    int L = 2000;
    int C = 1000000;
    double rho = 1.2;
    Simulator sim = Simulator(T, L, C);
    double lambda = rho*C/L;
    vector<Event*> events;
    generateArrivals(events, lambda, L, T);
    generateObs(events, lambda, T);
    sort(events.begin(), events.end(), cmpEvent);

    sim.simulateQueue(events, INT16_MAX);
    cout << "E[n]: " << sim.e_n << endl;
    cout << "P_idle: " << sim.p_idle << endl;
    cout << endl;
}

void simulateQ6() {
    vector<int> buffer_sizes{10, 25, 50};
    int T = 2000;
    int L = 2000;
    int C = 1000000;
    vector<vector<double>> p_loss;
    vector<vector<double>> e_n;
    CSVWriter writer;
    for (double rho = 0.25; rho <= 1.5; rho += 0.1) {
        Simulator sim = Simulator(T, L, C);
        double lambda = rho*C/L;
        vector<Event*> events;
        generateArrivals(events, lambda, L, T);
        generateObs(events, lambda, T);
        sort(events.begin(), events.end(), cmpEvent);
        vector<double> buff{rho};
        vector<double> loss{rho};
        for (auto& k : buffer_sizes) {
            sim.simulateQueue(events, k);
            buff.emplace_back(sim.e_n);
            loss.emplace_back(sim.p_loss);
            cout << "E[n]: " << sim.e_n << endl;
            cout << "P_loss: " << sim.p_loss << endl;
            cout << endl;
        }
        p_loss.emplace_back(loss);
        e_n.emplace_back(buff);
    }
    writer.writecsv(e_n, "q6e_n.csv");
    writer.writecsv(p_loss, "q6p_loss.csv");
}

int main() {
    srand(50);
    cout << "Simulating Q1" << endl;
    verifyDistr();
    cout << "Simulating Q3:" << endl;
    simulateQ3();
    cout << "Simulating Q4:" << endl;
    simulateQ4();
    cout << "Simulating Q6:" << endl;
    simulateQ6();
    return 0;
}
