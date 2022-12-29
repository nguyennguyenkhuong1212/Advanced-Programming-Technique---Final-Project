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
#include "HouseService.h"
#include "ReviewService.h"
using namespace std;

class MemberReview : public Review {
    private:
        House occupiedHouse;
    public:
        MemberReview(string comment = "", int score = 0, House occupiedHouse = House())
        : Review(comment, score), occupiedHouse(occupiedHouse){};
};

class Member{
    private:
        string username;
        string fullName;
        string phoneNumber;
        int creditPoint;
        vector <House> listedHouse;
        vector <MemberReview> reviews;

    public: 
        Member(string username = "", string fullName = "", string phoneNumber = "", int creditPoint = 0, vector <House> listedHouse = {})
        : username(username), fullName(fullName), phoneNumber(phoneNumber), creditPoint(creditPoint), listedHouse(listedHouse){};
};