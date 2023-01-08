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
#include "../RequestService/RequestService.h"
#include "../utils/Split.h"
using namespace std;

class RepoService{
    public:
        vector <Member> readMemberList(){
            vector <Member> memberList = {};
            ifstream inputFile;
            inputFile.open("RepoService/MemberList.csv", ios::in);
            string dataLine = "";
            while (true){
                getline(inputFile, dataLine);
                if (dataLine == "") break;
                vector<string> data = split(dataLine, ',');
                int id = stoi(data[0]);
                string username = data[1];
                string password = data[2];
                string fullName = data[3];
                string phoneNumber = data[4];
                int creditPoint = stoi(data[5]);
                vector <int> listedHouseId;
                vector <int> occupiedHouseId;
                vector <int> reviewId;
                vector <int> requestId;
                vector <string> temp = split(data[6], ' ');
                for (string id : temp){
                    listedHouseId.push_back(stoi(id));
                }
                temp = split(data[7], ' ');
                for (string id : temp){
                    occupiedHouseId.push_back(stoi(id));
                }
                temp = split(data[8], ' ');
                for (string id : temp){
                    reviewId.push_back(stoi(id));
                }
                temp = split(data[9], ' ');
                for (string id : temp){
                    requestId.push_back(stoi(id));
                }
                Member member(id, username, password, fullName, phoneNumber, creditPoint, listedHouseId, occupiedHouseId, reviewId, requestId);
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
                if (dataLine == "") break;
                vector<string> data = split(dataLine, ',');
                int id = stoi(data[0]);
                string location = data[1];
                string description = data[2];
                string availableTimeStart = data[3];
                string availableTimeEnd = data[4];
                vector <int> occupierId;
                vector <int> reviewId;
                vector <int> requestId;
                vector <string> temp = split(data[5], ' ');
                for (string id : temp){
                    occupierId.push_back(stoi(id));
                }
                temp = split(data[6], ' ');
                for (string id : temp){
                    reviewId.push_back(stoi(id));
                }
                temp = split(data[7], ' ');
                for (string id : temp){
                    requestId.push_back(stoi(id));
                }
                House house(id, location, description, availableTimeStart, availableTimeEnd, occupierId, reviewId, requestId);
                houseList.push_back(house);
                if (inputFile.eof()) break;
            }
            inputFile.close();
            return houseList;
        }

        vector <Request> readRequestList(){
            vector <Request> requestList = {};
            ifstream inputFile;
            inputFile.open("RepoService/RequestList.csv", ios::in);
            string dataLine = "";
            while (true){
                getline(inputFile, dataLine);
                if (dataLine == "") break;
                vector<string> data = split(dataLine, ',');
                int id = stoi(data[0]);
                int occupiedPersonId = stoi(data[1]);
                int occupiedHouseId = stoi(data[2]);
                string timeStart = data[3];
                string timeEnd = data[4];
                Request request(id, occupiedPersonId, occupiedHouseId, timeStart, timeEnd);
                requestList.push_back(request);
                if (inputFile.eof()) break;
            }
            inputFile.close();
            return requestList;
        }

        vector <HouseReview> readHouseReviewList(){
            vector <HouseReview> houseReviewList = {};
            ifstream inputFile;
            inputFile.open("RepoService/HouseReviewList.csv", ios::in);
            string dataLine = "";
            while (true){
                getline(inputFile, dataLine);
                if (dataLine == "") break;
                vector<string> data = split(dataLine, ',');
                int id = stoi(data[0]);
                string comment = data[1];
                int score = stoi(data[2]);
                int occupiedPersonId = stoi(data[3]);
                HouseReview review(id, comment, score, occupiedPersonId);
                houseReviewList.push_back(review);
                if (inputFile.eof()) break;
        }
            inputFile.close();
            return houseReviewList;
        }

        vector <MemberReview> readMemberReviewList(){
            vector <MemberReview> memberReviewList = {};
            ifstream inputFile;
            inputFile.open("RepoService/MemberReviewList.csv", ios::in);
            string dataLine = "";
            while (true){
                getline(inputFile, dataLine);
                if (dataLine == "") break;
                vector<string> data = split(dataLine, ',');
                int id = stoi(data[0]);
                string comment = data[1];
                int score = stoi(data[2]);
                int occupiedHouseId = stoi(data[3]);
                int hostId = stoi(data[4]);
                MemberReview review(id, comment, score, occupiedHouseId, hostId);
                memberReviewList.push_back(review);
                if (inputFile.eof()) break;
        }
            inputFile.close();
            return memberReviewList;
        }

        void writeMemberListIntoFile(vector<Member> MemberList, bool append){
            ofstream outputFile;
            outputFile.open("RepoService/MemberList.csv", (append ? ios::app : ios::out));
            if (!outputFile.is_open()){
                cout << "Could not open file for writing." << endl;
                return;
            }
            for (Member member : MemberList){
                outputFile << member.toDataLine() << endl;
            }
            outputFile.close();
        } 

        void writeHouseListIntoFile(vector<House> HouseList, bool append){
            ofstream outputFile;
            outputFile.open("RepoService/HouseList.csv", (append ? ios::app : ios::out));
            if (!outputFile.is_open()){
                cout << "Could not open file for writing." << endl;
                return;
            }
            for (House house : HouseList){
                outputFile << house.toDataLine() << endl;
            }
            outputFile.close();
        }

        void writeRequestListIntoFile(vector<Request> RequestList, bool append){
            ofstream outputFile;
            outputFile.open("RepoService/RequestList.csv", (append ? ios::app : ios::out));
            if (!outputFile.is_open()){
                cout << "Could not open file for writing." << endl;
                return;
            }
            for (Request request : RequestList){
                outputFile << request.toDataLine() << endl;
            }
            outputFile.close();
        }

        void writeHouseReviewListIntoFile(vector<HouseReview> HouseReviewList, bool append){
            ofstream outputFile;
            outputFile.open("RepoService/HouseReviewList.csv", (append ? ios::app : ios::out));
            if (!outputFile.is_open()){
                cout << "Could not open file for writing." << endl;
                return;
            }
            for (HouseReview review : HouseReviewList){
                outputFile << review.toDataLine() << endl;
            }
            outputFile.close();
        }

        void writeMemberReviewListIntoFile(vector<MemberReview> MemberReviewList, bool append){
            ofstream outputFile;
            outputFile.open("RepoService/MemberReviewList.csv", (append ? ios::app : ios::out));
            if (!outputFile.is_open()){
                cout << "Could not open file for writing." << endl;
                return;
            }
            for (MemberReview review : MemberReviewList){
                outputFile << review.toDataLine() << endl;
            }
            outputFile.close();
        }
};

