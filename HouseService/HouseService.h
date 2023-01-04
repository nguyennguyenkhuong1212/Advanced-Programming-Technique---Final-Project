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
#include "../ReviewService/ReviewService.h"
using namespace std;

class HouseReview : public Review {
    private:
        int occupiedPersonId;
        
    public:
        HouseReview(int id = 0, string comment = "", int score = 0, int occupiedPersonId = 0)
        : Review(id, comment, score), occupiedPersonId(occupiedPersonId){};

        string toDataLine(){
            stringstream ss;
            ss << id << ",";
            ss << comment << ",";
            ss << score << ",";
            ss << occupiedPersonId << ",";
            return ss.str();
        }
};

class House{
    private:
        int id;
        string location;
        string description;
        string availableTimeStart;
        string availableTimeEnd;
        vector <int> reviewId;
        vector <int> requestId;
    
    public:
        House(int id = 0, string location = "", string description = "", string availableTimeStart = 0, string availableTimeEnd = 0, vector <int> reviewId = {}, vector <int> requestId = {})
        : id(id), location(location), description(description), availableTimeStart(availableTimeStart), availableTimeEnd(availableTimeEnd), reviewId(reviewId), requestId(requestId){};

        string toDataLine(){
            stringstream ss;
            ss << id << ",";
            ss << location << ",";
            ss << description << ",";
            ss << availableTimeStart << ",";
            ss << availableTimeEnd << ",";
            for (int i: reviewId){
                ss << i << " ";
            }
            return ss.str();
        }
        
        friend class Member;
};