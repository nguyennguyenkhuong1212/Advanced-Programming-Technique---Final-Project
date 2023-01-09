#ifndef MEMBERSERVICE_H
#define MEMBERSERVICE_H
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

        friend class Menu;
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
        vector <int> occupiedHouseId;
        vector <int> reviewId;
        vector <int> requestId;
        
    public: 
        Member(){};

        Member(int id, string username, string password, string fullName, string phoneNumber, int creditPoint = 0, vector <int> listedHouseId = {}, vector <int> occupiedHouseId = {}, vector <int> reviewId = {}, vector <int> requestId = {})
        : id(id), username(username), password(password), fullName(fullName), phoneNumber(phoneNumber), creditPoint(creditPoint), listedHouseId(listedHouseId), occupiedHouseId(occupiedHouseId), reviewId(reviewId), requestId(requestId){};

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
            for (int i: occupiedHouseId){
                ss << i << (++id != occupiedHouseId.size() ? " " : "");
            }
            ss << ",";
            id = 0;
            for (int i: reviewId){
                ss << i << (++id != reviewId.size() ? " " : "");
            }
            ss << ",";
            id = 0;
            for (int i: requestId){
                ss << i << (++id != requestId.size() ? " " : "");
            }
            return ss.str();
        }

        string toDisplayLine(string prefix = ""){
            stringstream ss;
            ss << "\n";
            ss << prefix << "ID: " << id << "\n";
            ss << prefix << "Name: " << fullName << "\n";
            return ss.str();
        }

        vector <string> toStringArray(bool getAllInfo = false) {
            vector <string> res;
            res.push_back(to_string(id));
            res.push_back(username);
            if (getAllInfo) {
                res.push_back(password);
            }
            res.push_back(fullName);
            if (getAllInfo) {
                res.push_back(phoneNumber);
                res.push_back(to_string(creditPoint));
            }
            return res;
        }

        friend class RepoService;
        friend class MainMenu;
        friend class MemberMenu;
        friend class GuestMenu;
        friend class Menu;
        friend bool findMemberById(int id, vector <Member> memberList, Member& res);
};

bool findMemberById(int id, vector <Member> memberList, Member& res){
    for (Member member : memberList){
        if (member.id == id){
            res = member;
            return true;
        }
    }
    return false;
}

#endif