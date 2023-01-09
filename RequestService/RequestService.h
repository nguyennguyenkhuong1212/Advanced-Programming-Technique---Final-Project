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
        bool isDelete;

    public:
        Request(int id = 0, int occupiedPersonId = 0, int occupiedHouseId = 0, string timeStart = "", string timeEnd = "", bool isDelete = false)
        : id(id), occupiedPersonId(occupiedPersonId), occupiedHouseId(occupiedHouseId), timeStart(timeStart), timeEnd(timeEnd), isDelete(isDelete){};

        string toDataLine(){
            stringstream ss;
            ss << id << ",";
            ss << occupiedPersonId << ",";
            ss << occupiedHouseId << ",";
            ss << timeStart << ",";
            ss << timeEnd << ",";
            ss << isDelete;
            return ss.str();
        }
};