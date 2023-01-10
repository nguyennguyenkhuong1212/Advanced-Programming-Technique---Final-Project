#ifndef HOUSESERVICE_H
#define HOUSESERVICE_H
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
#include "../DateService/Date.h"
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
        Date availableTimeStart;
        Date availableTimeEnd;
        int consumingPoints;
        double minimumRating; // minimum rating of occupier if he/she wants to occupy the house
        vector <int> occupierId;
        vector <int> reviewId;
        vector <int> requestId;
        bool isListed;
    
    public:
        House(){};

        House(int id, string location, string description, Date availableTimeStart, Date availableTimeEnd, int consumingPoints, double minimumRating, vector <int> occupierId = {}, vector <int> reviewId = {}, vector <int> requestId = {}, bool isListed = true)
        : id(id), location(location), description(description), availableTimeStart(availableTimeStart), availableTimeEnd(availableTimeEnd), consumingPoints(consumingPoints), minimumRating(minimumRating), occupierId(occupierId), reviewId(reviewId), requestId(requestId), isListed(isListed){};

        string toDataLine(){
            stringstream ss;
            ss << id << ",";
            ss << location << ",";
            ss << description << ",";
            ss << availableTimeStart.toDataLine() << ",";
            ss << availableTimeEnd.toDataLine() << ",";
            ss << consumingPoints << ",";
            ss << setprecision(2) << fixed << minimumRating << ",";
            int id = 0;
            for (int i: occupierId){
                ss << i << (++id != occupierId.size() ? " " : "");
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
            ss << ",";
            ss << isListed;
            return ss.str();
        }

        string toDisplayLine(string prefix = ""){
            stringstream ss;
            ss << "\n";
            ss << prefix << "House ID: " << id << "\n";
            ss << prefix << "Location: " << location << "\n";
            ss << prefix << "Description: " << description << "\n";
            ss << prefix << "Consuming Points: " << consumingPoints << "\n";
            return ss.str();
        }

        vector <string> toStringArray(){
            vector <string> res;
            res.push_back(to_string(id));
            res.push_back(location);
            res.push_back(description);
            res.push_back(availableTimeStart.toDisplayLine());
            res.push_back(availableTimeEnd.toDisplayLine());
            res.push_back(to_string(consumingPoints));
            stringstream ss;
            ss << setprecision(2) << fixed << minimumRating;
            res.push_back(ss.str());
            return res;
        }
        
        friend class RepoService;
        friend class MemberMenu;
        friend class Menu;
        friend bool findHouseById(int id, vector <House> houseList, House& res);
};

bool findHouseById(int id, vector <House> houseList, House& res){
    for(House house: houseList){
        if (house.id == id){
            res = house;
            return true;
        }
    }
    return false;
}

#endif
