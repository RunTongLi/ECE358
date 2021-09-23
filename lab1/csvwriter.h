#ifndef _CSV_WRITER_
#define _CSV_WRITER_

#include <vector>
#include <string>

class CSVWriter {
  public:
    void writecsv(std::vector<std::vector<double>> data, std::string name);
};

#endif
