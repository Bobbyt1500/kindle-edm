#include "data.h"
#include <iostream>

void Data::parse_data(std::string data) {
    if (data.size() == 0) return;
    

    int found = data.find(',');
    int last_found = found;

    // First value is rpm
    rpm = std::stoi(data.substr(0, found));

    for(int i = 1; i < 14; ++i) {

        // Find and get the next value
        found = data.find(',', last_found+1);
        std::string value_str = data.substr(last_found+1, (found-last_found)-1);

        float valuef = std::stof(value_str);
        int value = std::stoi(value_str);

        // Assign value to variable depending on value index "i"
        switch (i) {
            case 1:
                map = valuef;
                break;

            case 2:
                cht = value;
                break;
            
            case 3:
                egt = value;
                break;
            
            case 4:
                oilp = value;
                break;
            
            case 5:
                oilt = value;
                break;

            case 6:
                fuelL = value;
                break;
            
            case 7:
                fuelR = value;
                break;
            
            case 8:
                fuelf = valuef;
                break;
            
            case 9:
                volts = valuef;
                break;
            
            case 10:
                amps = value;
                break;
            
            case 11:
                fuelp = value;
                break;
            
            case 12:
                oat = value;
                break;
            
            case 13:
                on = value;
                break;


        }

        last_found = found;
    }
}