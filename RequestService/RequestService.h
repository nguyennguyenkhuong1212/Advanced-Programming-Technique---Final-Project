#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <functional>
#include <algorithm>
using namespace std;

class Request {
    private:
        int id;
        int occupiedPersonId;
        int occupiedHouseId;
        string timeStart;
        string timeEnd;

    public:
        Request(int id = 0, int occupiedPersonId = 0, int occupiedHouseId = 0, string timeStart = "", string timeEnd = "")
        : id(id), occupiedPersonId(occupiedPersonId), occupiedHouseId(occupiedHouseId), timeStart(timeStart), timeEnd(timeEnd){};

        string toDataLine(){
            stringstream ss;
            ss << id << ",";
            ss << occupiedPersonId << ",";
            ss << occupiedHouseId << ",";
            ss << timeStart << ",";
            ss << timeEnd;
        }
};