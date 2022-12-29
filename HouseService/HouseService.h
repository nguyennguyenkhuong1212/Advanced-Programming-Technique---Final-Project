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
#include "ReviewService.h"
#include "MemberService.h"
using namespace std;

class HouseReview : public Review {
    private:
        Member occupiedPerson;
    public:
        HouseReview(string comment = "", int score = 0, Member occupiedPerson = Member())
        : Review(comment, score), occupiedPerson(occupiedPerson){};
};

class House{
    private:
        string location;
        string description;
        int availableTimeStart;
        int availableTimeEnd;
        vector <HouseReview> reviews;
    
    public:
        House(string location = "", string description = "", int availableTimeStart = 0, int availableTimeEnd = 0)
        : location(location), description(description), availableTimeStart(availableTimeStart), availableTimeEnd(availableTimeEnd){};
        
        friend class Member;
};