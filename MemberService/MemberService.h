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
        int hostId;
        
    public:
        MemberReview(int id, string comment = "", int score = 0, int occupiedHouseId = 0, int hostId = 0)
        : Review(id, comment, score), occupiedHouseId(occupiedHouseId), hostId(hostId){};

        string toDataLine(){
            stringstream ss;
            ss << id << ",";
            ss << comment << ",";
            ss << score << ",";
            ss << occupiedHouseId << ",";
            ss << hostId;
            return ss.str();
        }
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
        vector <int> reviewId;
        vector <int> requestId;

    public: 
        Member(int id = 0, string username = "", string password = " ", string fullName = "", string phoneNumber = "", int creditPoint = 0, vector <int> listedHouseId = {}, vector <int> reviewId = {}, vector <int> requestId = {})
        : id(id), username(username), password(password), fullName(fullName), phoneNumber(phoneNumber), creditPoint(creditPoint), listedHouseId(listedHouseId), reviewId(reviewId), requestId(requestId){};

        string toDataLine(){
            stringstream ss;
            ss << id << ",";
            ss << username << ",";
            ss << password << ",";
            ss << fullName << ",";
            ss << phoneNumber << ",";
            ss << creditPoint << ",";
            int id = 0;
            for (int i: listedHouseId){
                ss << i << (++id != listedHouseId.size() ? " " : "");
            }
            ss << ",";
            id = 0;
            for (int i: reviewId){
                ss << i << (++id != reviewId.size() ? " " : "");
            }
            return ss.str();
        }

        friend class RepoService;
};