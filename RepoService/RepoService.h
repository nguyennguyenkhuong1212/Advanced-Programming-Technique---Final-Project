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
                vector <int> reviewsId;
                vector <string> temp = split(data[6], ' ');
                for (string id : temp){
                    listedHouseId.push_back(stoi(id));
                }
                temp = split(data[7], ' ');
                for (string id : temp){
                    reviewsId.push_back(stoi(id));
                }
                Member member(id, username, password, fullName, phoneNumber, creditPoint, listedHouseId, reviewsId);
                memberList.push_back(member);
                if (inputFile.eof()) break;
            }
            inputFile.close();
            return memberList;
        }
};

