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
#include "../HouseService/HouseService.h"
#include "../MemberService/MemberService.h"
#include "../utils/Split.h"
using namespace std;

class RepoService{
    public:
        vector <Member> readMemberList(){
            vector <Member> memberList;
            ifstream inputFile;
            inputFile.open("RepoService/MemberList.csv", ios::in);
            string dataLine = "";
            while (true){
                getline(inputFile, dataLine);
                vector<string> data = split(dataLine, ',');
                int id = stoi(data[0]);
                string username = data[1];
                string password = data[2];
                string fullName = data[3];
                string phoneNumber = data[4];
                int creditPoint = stoi(data[5]);
                vector <int> listedHouseId;
                vector <int> reviewId;
                vector <string> temp = split(data[6], ' ');
                for (string id : temp){
                    listedHouseId.push_back(stoi(id));
                }
                temp = split(data[7], ' ');
                for (string id : temp){
                    reviewId.push_back(stoi(id));
                }
                Member member(id, username, password, fullName, phoneNumber, creditPoint, listedHouseId, reviewId);
                memberList.push_back(member);
                if (inputFile.eof()) break;
            }
            inputFile.close();
            return memberList;
        }

        vector <House> readHouseList(){
            vector <House> houseList;
            ifstream inputFile;
            inputFile.open("RepoService/HouseList.csv", ios::in);
            string dataLine = "";
            while (true){
                getline(inputFile, dataLine);
                vector<string> data = split(dataLine, ',');
                int id = stoi(data[0]);
                string location = data[1];
                string description = data[2];
                string availableTimeStart = data[3];
                string availableTimeEnd = data[4];
                vector <int> reviewId;
                vector <int> requestId;
                vector <string> temp = split(data[5], ' ');
                for (string id : temp){
                    reviewId.push_back(stoi(id));
                }
                temp = split(data[6],'');
                for (string id : temp){
                    requestId.push_back(stoi(id));
                }
                House house(id, location, description, availableTimeStart, availableTimeEnd, reviewId, requestId);
                houseList.push_back(house);
                if (inputFile.eof()) break;
            }
            inputFile.close();
            return houseList;
        }
};

