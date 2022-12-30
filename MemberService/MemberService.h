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

class MemberReview : public Review {
    private:
        int occupiedHouseId;
    public:
        MemberReview(int id, string comment = "", int score = 0, int occupiedHouseId = 0)
        : Review(id, comment, score), occupiedHouseId(occupiedHouseId){};
};

class Member{
    private:
        int id;
        string username;
        string password;
        string fullName;
        string phoneNumber;
        int creditPoint;
        vector <int> listedHouseId;
        vector <int> reviewsId;

    public: 
        Member(int id = 0, string username = "", string password = " ", string fullName = "", string phoneNumber = "", int creditPoint = 0, vector <int> listedHouseId = {}, vector <int> reviewsId = {})
        : id(id), username(username), password(password), fullName(fullName), phoneNumber(phoneNumber), creditPoint(creditPoint), listedHouseId(listedHouseId), reviewsId(reviewsId){};

        string toDataLine(){
            stringstream ss;
            ss << id << ",";
            ss << username << ",";
            ss << password << ",";
            ss << fullName << ",";
            ss << phoneNumber << ",";
            ss << creditPoint << ",";
            for (int id: listedHouseId){
                ss << id << " ";
            }
            ss << ",";
            for (int id: reviewsId){
                ss << id << " ";
            }
            return ss.str();
        }

        friend class RepoService;
};