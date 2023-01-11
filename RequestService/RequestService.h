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
#include "../MemberService/MemberService.h"
#include "../DateService/Date.h"
using namespace std;

class Request {
    private:
        int id;
        int occupiedPersonId;
        int occupiedHouseId;
        Date timeStart;
        Date timeEnd;
        bool isApproved;
        bool isDelete;

    public:
        Request(){};

        Request(int id, int occupiedPersonId, int occupiedHouseId, Date timeStart, Date timeEnd, bool isApproved = false, bool isDelete = false)
        : id(id), occupiedPersonId(occupiedPersonId), occupiedHouseId(occupiedHouseId), timeStart(timeStart), timeEnd(timeEnd), isApproved(isApproved), isDelete(isDelete){};

        string toDataLine(){
            stringstream ss;
            ss << id << ",";
            ss << occupiedPersonId << ",";
            ss << occupiedHouseId << ",";
            ss << timeStart.toDataLine() << ",";
            ss << timeEnd.toDataLine() << ",";
            ss << isApproved << ",";
            ss << isDelete;
            return ss.str();
        }

        vector <string> toStringArray(bool special = false){
            vector <string> res;
            res.push_back(to_string(id));
            if (!special) res.push_back(to_string(occupiedPersonId));
            res.push_back(to_string(occupiedHouseId));
            res.push_back(timeStart.toDataLine());
            res.push_back(timeEnd.toDataLine());
            if (!special) res.push_back((isApproved ? "Yes" : "No"));
            return res;
        }

        bool isOverlapped(Date timeStart, Date timeEnd, bool special = false){
            Date tempStart = this->timeStart;
            Date tempEnd = this->timeEnd;
            if (special) return (tempEnd >= timeStart && timeEnd >= tempStart);
            return (tempEnd > timeStart && timeEnd > tempStart);
        }

        friend class MemberMenu;
};