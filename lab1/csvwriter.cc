#include "csvwriter.h"
#include <vector>
#include <string>
#include <fstream>

using namespace std;

void CSVWriter::writecsv(const vector<vector<double>> data, string name) {
    ofstream ofile;
    ofile.open(name);
    for (auto& row : data) {
        for (const auto& item : row) {
            ofile << item << ",";
        }
        ofile << endl;
    }
    ofile.close();
}

