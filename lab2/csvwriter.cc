#include "csvwriter.h"
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Writes data from vector into csv
void CSVWriter::writecsv(const vector<vector<double>> data, string name) {
    ofstream ofile;
    ofile.open(name);
    for (auto& row : data) {
        for (int i = 0; i < row.size(); ++i) {
            ofile << row.at(i);
            if (i < row.size()-1) {
                ofile << ",";
            }
        }
        ofile << endl;
    }
    ofile.close();
}

