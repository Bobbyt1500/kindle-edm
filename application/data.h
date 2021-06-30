#ifndef KINDLE_EDM_DATA
#define KINDLE_EDM_DATA

#include <string>

class Data {
    public:
    int rpm, cht, egt, oilt, oilp, fuelL, fuelR, fuelp, amps, oat, on;
    float map, fuelf, volts;
    void parse_data(std::string data);
};

#endif