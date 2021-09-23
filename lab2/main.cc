#include <iostream>
#include <vector>
#include "channel.h"
#include "csvwriter.h"

using namespace std;

double R = 1e6;    // Speed of the LAN/channel/bus (bps)
double D = 10;     // Distance between nodes (m)
double S = 2*10e8; // Propagation Speed (m/s)

void simulateQ1() {
    int t = 1000;
    vector<int> avgArrivalTimes = {7, 10, 20};
    vector<vector<double>> efficiency(4, vector<double>(5));
    vector<vector<double>> throughput(4, vector<double>(5));
    CSVWriter writer;
    efficiency.at(0) = {20, 40, 60, 80, 100};
    throughput.at(0) = {20, 40, 60, 80, 100};
    for (int i = 1; i < 4; ++i) {
        for (int j = 0; j < 5; ++j) {
            double N = (j+1)*20;
            Channel channel = Channel(true, N, avgArrivalTimes.at(i-1), t, R, D, S);
            channel.simulate(efficiency.at(i).at(j), throughput.at(i).at(j));
        }
    }
    writer.writecsv(efficiency, "efficiency_1.csv");
    writer.writecsv(throughput, "throughput_1.csv");
}

void simulateQ2() {
    int t = 1000;
    vector<int> avgArrivalTimes = {7, 10, 20};
    vector<vector<double>> efficiency(4, vector<double>(5));
    vector<vector<double>> throughput(4, vector<double>(5));
    CSVWriter writer;
    efficiency.at(0) = {20, 40, 60, 80, 100};
    throughput.at(0) = {20, 40, 60, 80, 100};
    for (int i = 1; i < 4; ++i) {
        for (int j = 0; j < 5; ++j) {
            double N = (j+1)*20;
            Channel channel = Channel(false, N, avgArrivalTimes.at(i-1), t, R, D, S);
            channel.simulate(efficiency.at(i).at(j), throughput.at(i).at(j));
        }
    }
    writer.writecsv(efficiency, "efficiency_2.csv");
    writer.writecsv(throughput, "throughput_2.csv");
}

int main() {
    srand(0);
    simulateQ1();
    simulateQ2();
    return 0;
}
