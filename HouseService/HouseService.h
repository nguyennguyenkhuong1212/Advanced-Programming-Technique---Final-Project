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
};

class House{
    private:
        int id;
        string location;
        string description;
        int availableTimeStart;
        int availableTimeEnd;
        vector <int> reviewId;
    
    public:
        House(int id = 0, string location = "", string description = "", int availableTimeStart = 0, int availableTimeEnd = 0)
        : id(id), location(location), description(description), availableTimeStart(availableTimeStart), availableTimeEnd(availableTimeEnd){};
        
        friend class Member;
};