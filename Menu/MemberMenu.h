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
#include <conio.h>
#include "Menu.h"
#include "../utils/Delay.h"
#include "../utils/ReadString.h"
#include "../utils/ReadInt.h"
#include "../TableFormatter/TableFormatter.h"
#include "../DateService/Date.h"
using namespace std;

class MemberMenu : public Menu{
    private: 
        Member curMember;

    public:
        MemberMenu(vector<House> houseList = {}, vector<Member> memberList = {}, vector<HouseReview> houseReviewList = {}, vector<MemberReview> memberReviewList = {}, vector<Request> requestList = {}, Member curMember = Member()) 
        : Menu({}, houseList, memberList, houseReviewList, memberReviewList, requestList), curMember(curMember){
            this->addOption(Option("1", "View all account information", [&]() -> void {viewInformation();}));
            this->addOption(Option("2", "List a house", [&]() -> void {listHouse();}));
            this->addOption(Option("3", "Unlist a house", [&]() -> void {unlistHouse();}));
            this->addOption(Option("4", "Search for all available and suitable houses in a city", [&]() -> void {searchForAllAvailableAndSuitableHouseInACity();}));
            this->addOption(Option("5", "Request to occupy a house", [&]() -> void {requestToOccupy();}));
            this->addOption(Option("6", "View all requests to your listed house", [&]() -> void {viewAllRequests();}));
            this->addOption(Option("7", "Accept a request to your listed house and reject all the others", [&]() -> void {acceptARequestToYourListedHouse();}));
            this->addOption(Option("8", "Rate for your occupied house", [&]() -> void {rateOccupiedHouse();}));
            this->addOption(Option("9", "Rate occupiers who had used your house", [&]() -> void {rateOccupier();}));
            this->addOption(Option("10", "Top up money (1 dollar : 1 credit points)", [&]() -> void {topUp();}));
            this->addOption(Option("11", "View all reviews about yourself", [&]() -> void {viewAllReviewAboutYourself();}));
            this->addOption(Option("12", "View all reviews about your listed house", [&]() -> void {viewAllReviewAboutYourHouse();}));
            this->addOption(Option("13", "Return to main menu"));
            this->addOption(Option("14", "Exit the program", [&]() -> void {stop();}));
        }

        void viewInformation(){
            vector <string> labels = {"ID", "Username", "Password", "Full Name", "Phone Number", "Credit Points", "Score"};
            TableFormatter table(labels);
            vector <string> temp = curMember.toStringArray(true);
            stringstream ss;
            ss << setprecision(2) << fixed << getScore(curMember);
            temp.push_back(ss.str());
            table.addRow(temp);
            table.display("\t");
            waitUntilKeyPressed("\t");
        }

        void listHouse(){
            if (curMember.listedHouseId != -1){
                cout<<"\n\tYou already listed a house. Cannot list more.\n";
                delay(1500);
                return;
            }
            string location;
            string description;
            Date availableTimeStart;
            Date availableTimeEnd;
            int consumingPoints;
            double minimumRating;
            
            cout << "Enter location: ";
            readString(location);
            cout << "Enter description: ";
            readString(description);
            cout << "Available from: \n";
            if (!readDate(availableTimeStart, "\t")){
                delay(1500);
                return;
            };
            cout << "Available until: \n";
            if (!readDate(availableTimeEnd, "\t")){
                delay(1500);
                return;
            };
            cout << "Enter consuming points per hour to occupy: ";
            if (!readInt(consumingPoints)){
                cout << "\n\tInvalid consuming points. Return back...\n";
                delay(1500);
                return;
            };
            cout << "Enter minimum rating required: ";
            cin >> minimumRating;

            int id = houseList.size();
            House tempHouse(id, location, description, availableTimeStart, availableTimeEnd, consumingPoints, minimumRating);
            for (int i = 0; i < memberList.size(); i++) {
                if (memberList[i].id == curMember.id){
                    memberList[i].listedHouseId = id;
                    break;
                }
            }
            houseList.push_back(tempHouse);
            waitUntilKeyPressed("\t");
        }

        void unlistHouse(){
            if (curMember.listedHouseId == -1){
                cout << "\n\tYou listed no house. Returning back...\n";
                delay(1500);
                return;
            }
            cout << "\n\tThis is your listed house:\n";
            if (!viewAllHouseListed(curMember, "\t")) {
                waitUntilKeyPressed("\t");
                return;
            }
            cout << "\n\tEnter a house's ID to unlist it: ";
            int houseId;
            if (!readInt(houseId) || houseId != curMember.listedHouseId){
                cout << "\n\tInvalid house ID. Return back...\n";
                delay(1500);
                return;
            };
            bool found = false;
            for (int i = 0; i < houseList.size(); i++) {
                if (!houseList[i].isListed) continue;
                if (houseList[i].id == houseId){
                    curMember.listedHouseId = -1;
                    houseList[i].isListed = false;
                    found = true;
                }
            }
            if (!found){
                cout << "\n\tCannot find this house. Returning back...\n";
                delay(1500);
                return;
            }
            waitUntilKeyPressed("\t");
        }

        void searchForAllAvailableAndSuitableHouseInACity(){
            vector <string> labels = {"ID", "Location", "Description", "Available Time Start", "Available Time End", "Consuming Points (per hour)", "Minimum Score Required"};
            TableFormatter table(labels);
            string location;
            vector <string> tempLabels = {"ID", "Location"};
            TableFormatter table2(tempLabels);
            table2.addRow({"1", "Ho Chi Minh City"});
            table2.addRow({"2", "Hue"});
            table2.addRow({"3", "Ha Noi"});
            cout << "\n";
            table2.display("\t");
            cout << "\n";
            cout << "Enter location ID: ";
            readString(location);
            if (location != "1" && location != "2" && location != "3"){
                cout << "Invalid location. Return back...\n";
                delay(1500);
                return;
            }
            if (location == "1") location = "Ho Chi Minh City";
            if (location == "2") location = "Hue";
            if (location == "3") location = "Ha Noi";
            bool found = false;
            for (House house: houseList){
                if (house.location == location && house.consumingPoints <= curMember.creditPoint && house.id != curMember.listedHouseId && getScore(curMember) >= house.minimumRating){
                    table.addRow(house.toStringArray());
                    found = true;
                }
            }
            if (!found){
                cout << "\n\tNo house meets your conditions. Return back...\n";
                delay(1500);
                return;
            }
            table.display("\t");
            waitUntilKeyPressed("\t");
        };

        void requestToOccupy(){
            cout << "\n\tThis is all the house meet your conditions: \n";
            vector <string> labels = {"ID", "Location", "Description", "Available Time Start", "Available Time End", "Consuming Points (per hour)", "Minimum Score Required"};
            TableFormatter table(labels);
            bool found = false;
            for (House house: houseList){
                if (house.consumingPoints <= curMember.creditPoint && house.id != curMember.listedHouseId && getScore(curMember) >= house.minimumRating){
                    table.addRow(house.toStringArray());
                    found = true;
                }
            }
            if (!found){
                cout << "\n\tNo house meets your conditions. Return back...\n";
                delay(1500);
                return;
            }
            table.display("\t");
            int id;
            cout << "\n\tEnter the ID of the house you want to occupy: ";
            if (!readInt(id)){
                cout << "\n\tInvalid house ID. Returning back...\n";
                delay(1500);
                return;
            };
            House res;
            if (!findHouseById(id, houseList, res)) {
                cout << "\n\tThis house is unlisted or not existed. Return back...\n";
                delay(1500);
                return;
            }
            else {
                if (!res.isListed){
                    cout << "\n\tThis house is unlisted or not existed. Return back...\n";
                    delay(1500);
                    return;
                }
            }
            Date timeStart;
            Date timeEnd;
            cout << "\n\tEnter the start time of your occupying period: \n";
            if (!readDate(timeStart, "\t")){
                delay(1500);
                return;
            };
            cout << "\n\tEnter the end time of your occupying period: \n";
            if (!readDate(timeEnd, "\t")){
                delay(1500);
                return;
            };
            if (timeStart > res.availableTimeEnd || timeEnd < res.availableTimeStart){
                cout << "\n\tInvalid input. Return back...\n";
                delay(1500);
                return;
            }
            for (Request request: requestList){
                if (request.isDelete) continue;
                if (request.occupiedPersonId != curMember.id) continue;
                if (request.isApproved && request.isOverlapped(timeStart, timeEnd)){
                    cout << "\n\tTime overlapped with another approved request. Return back...\n";
                    delay(1500);
                    return;
                }
                if (request.occupiedHouseId == id && request.occupiedPersonId == curMember.id && request.isOverlapped(timeStart, timeEnd, true)){
                    cout << "\n\tYou have a request overlapped with this request. Your request will be automatically merged...\n";
                    timeStart = (timeStart < request.timeStart ? timeStart : request.timeStart);
                    timeEnd = (timeEnd > request.timeEnd ? timeEnd : request.timeEnd);
                    requestList[request.id].timeStart = timeStart;
                    requestList[request.id].timeEnd = timeEnd;
                    cout << "\n\tThis new request has been merged. Total consuming points: " << calDifference(timeStart, timeEnd) * houseList[id].consumingPoints << "\n";
                    waitUntilKeyPressed("\t");
                    return;
                }
            }
            Request newRequest(requestList.size(), curMember.id, id, timeStart, timeEnd);
            requestList.push_back(newRequest);
            cout << "\n\tThis new request has been created. Total consuming points: " << calDifference(timeStart, timeEnd) * houseList[id].consumingPoints << "\n";
            waitUntilKeyPressed("\t");
        }

        void viewAllRequests(){
            cout << "\n\tThis is your listed house:\n";
            if (curMember.listedHouseId == -1){
                cout << "\n\tYou listed no house. Returning back...\n";
                delay(1500);
                return;
            }
            viewAllHouse(curMember, "\t\t"); 
            cout << "\n\tEnter a house's ID to view all the requests: ";
            int houseId;
            if (!readInt(houseId) || houseId != curMember.listedHouseId){
                cout << "\n\tInvalid house ID. Return back...\n";
                delay(1500);
                return;
            };
            vector<string> labels = {"ID", "Occupier ID", "House ID", "Time Start", "Time End", "Is Approved"};
            TableFormatter table(labels);
            bool found = false;
            for (Request request : requestList){
                if (!request.occupiedHouseId == houseId || request.isDelete) continue;
                table.addRow(request.toStringArray());
                found = true;
            }
            if (!found) {
                cout << "\n\tThis house has no requests. Return back...\n";
                delay(1500);
                return;
            }
            table.display("\t");   
            waitUntilKeyPressed("\t");
        }

        void acceptARequestToYourListedHouse(){
            cout << "\n\tThis is your listed house:\n";
            if (curMember.listedHouseId == -1){
                cout << "\n\tYou listed no house. Returning back...\n";
                delay(1500);
                return;
            }
            viewAllHouse(curMember, "\t\t"); 
            cout << "\n\tEnter a house's ID to view all the requests: ";
            int houseId;
            if (!readInt(houseId) || houseId != curMember.listedHouseId){
                cout << "\n\tInvalid house ID. Return back...\n";
                delay(1500);
                return;
            };
            vector<string> labels = {"ID", "Occupier ID", "House ID", "Time Start", "Time End", "Is Approved"};
            TableFormatter table(labels);
            bool found = false;
            for (Request request : requestList){
                if (!request.occupiedHouseId == houseId || request.isDelete) continue;
                table.addRow(request.toStringArray());
                found = true;
            }
            if (!found) {
                cout << "\n\tThis house has no requests. Return back...\n";
                delay(1500);
                return;
            }
            table.display("\t");   
            int requestId;
            cout << "\n\tEnter the request ID that you want to approve: ";
            if (!readInt(requestId)){
                cout << "\n\tInvalid request ID. Return back...\n";
                delay(1500);
                return;
            };
            found = false;
            for (Request request : requestList){
                if (request.isDelete) continue;
                if (request.id == requestId) continue;
                if (!request.isApproved) continue;
                if (!request.occupiedPersonId == requestList[requestId].occupiedPersonId) continue;
                if (!request.isOverlapped(requestList[requestId].timeStart, requestList[requestId].timeEnd)) continue;
                cout << "\n\t This person already occupied a house in this period of time. This request will be deleted. Return back...\n";
                requestList[requestId].isDelete = true;
                delay(1500);
                return;
            }
            for (Request request : requestList){
                if (!request.occupiedHouseId == houseId || request.isDelete) continue;
                if (!request.id == requestId) continue; 
                if (memberList[request.occupiedPersonId].creditPoint < (houseList[request.occupiedHouseId].consumingPoints) * calDifference(request.timeStart, request.timeEnd)){
                    cout << "\n\tThis person is out of credit points. This request will be deleted. Return back...\n";
                    requestList[requestId].isDelete = true;
                    delay(1500);
                    return;
                } 
                else {
                    requestList[requestId].isApproved = true;
                    memberList[request.occupiedPersonId].creditPoint -= (houseList[request.occupiedHouseId].consumingPoints) * calDifference(request.timeStart, request.timeEnd);
                    memberList[request.occupiedPersonId].occupiedHouseId.push_back(request.occupiedHouseId);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "\n\tCannot find this request. Return back...\n";
                delay(1500);
                return;
            }
            for (Request request : requestList){
                if (!request.occupiedHouseId == houseId || request.isDelete || request.id == requestId) continue;
                if (request.isOverlapped(requestList[requestId].timeStart, requestList[requestId].timeEnd)){
                    requestList[request.id].isDelete = true;
                }
            }
            waitUntilKeyPressed("\t");
        }

        void rateOccupiedHouse(){
            cout << "\n\tThis is all the house that you have occupied: \n";
            if (!viewAllHouseOccupied(curMember, "\t")){
                waitUntilKeyPressed("\t");
                return;
            }
            cout << "\n\tEnter a house's ID to rate it: ";
            int houseId;
            if (!readInt(houseId) || find(curMember.occupiedHouseId.begin(), curMember.occupiedHouseId.end(), houseId) == curMember.occupiedHouseId.end()){
                cout << "\n\tInvalid house ID. Return back...\n";
                delay(1500);
                return;
            };
            int score;
            cout << "\n\tEnter score: ";
            if (!readInt(score) || score > 10 || score < 1){
                cout << "\n\tInvalid score. Return back...\n";
                delay(1500);
                return;
            }
            string comment;
            cout << "\n\tEnter comment: ";
            readString(comment);
            HouseReview review(houseReviewList.size(), comment, score, curMember.id);
            houseList[houseId].reviewId.push_back(houseReviewList.size());
            houseReviewList.push_back(review);
            waitUntilKeyPressed("\t");
        }
        
        void topUp(){
            for (int i = 0; i < memberList.size(); i++){
                if (memberList[i].id == curMember.id){
                    int money = 0;
                    cout << "\n\tEnter the money that you use to top up: ";
                    if (!readInt(money)){
                        cout << "\n\tInvalid input. Return back...\n";
                        delay(1500);
                        return;
                    }
                    memberList[i].creditPoint += money;
                    break;
                }
            }
            waitUntilKeyPressed("\t");
        }

        void rateOccupier(){
            cout << "\n\tThis is your listed house:\n";
            if (curMember.listedHouseId == -1){
                cout << "\n\tYou listed no house. Returning back...\n";
                delay(1500);
                return;
            }
            viewAllHouse(curMember, "\t\t");
            cout << "\n\tEnter a house's ID to view all the occupiers: ";
            int houseId;
            if (!readInt(houseId) || houseId != curMember.listedHouseId){
                cout << "\n\tInvalid house ID. Return back...\n";
                delay(1500);
                return;
            };
            cout << "\n\tThis is all of people who occupied this house:\n";
            for (House house: houseList){
                if (house.id == houseId){
                    if (house.occupierId.size() == 0) {
                        cout << "\n\tNo one occupied this house. Return back...\n";
                        delay(1500);
                        return;
                    }
                    viewAllOccupiers(house, "\t\t");
                    break;
                }
            }
            cout << "\n\tEnter the occupier's ID that you want to rate: ";
            int occupierId;
            if (!readInt(occupierId)){
                cout << "\n\tInvalid occupier ID. Return back...\n";
                delay(1500);
                return;
            };
            cout << "\tEnter the score for this occupier: ";
            int score;
            if (!readInt(score)){
                cout << "\n\tInvalid score. Return back...\n";
                delay(1500);
                return;
            };
            cout << "\tEnter the comment for this occupier: ";
            string comment;
            readString(comment);
            MemberReview review(memberReviewList.size(), comment, score, houseId, curMember.id);
            memberList[occupierId].reviewId.push_back(memberReviewList.size());
            memberReviewList.push_back(review);
            cout << "\n";
            delay(1500);
            waitUntilKeyPressed("\t");
        }

        void viewAllReviewAboutYourself(){
            if (curMember.reviewId.size() == 0){
                cout << "\n\tThere is no reviews about you. Return back...\n";
                delay(1500);
                return;
            }
            vector <string> labels = {"ID", "Comment", "Score", "House Occupied", "Reviewer Name"};
            TableFormatter table(labels);
            for (int reviewId: curMember.reviewId){
                vector <string> row = memberReviewList[reviewId].toStringArray();
                row.push_back(memberList[memberReviewList[reviewId].hostId].fullName);
                table.addRow(row);
            }
            table.display("\t");
            waitUntilKeyPressed("\t");
        }

        void viewAllReviewAboutYourHouse(){
            if (curMember.listedHouseId == -1){
                cout << "\n\tYou listed no house. Returning back...\n";
                delay(1500);
                return;
            }
            cout << "\n\tThis is your listed house:\n";
            if (!viewAllHouseListed(curMember, "\t")) {
                waitUntilKeyPressed("\t");
                return;
            }
            if (houseList[curMember.listedHouseId].reviewId.size() == 0){
                cout << "\n\tThere is no reviews about your listed house. Returning back...\n";
                delay(1500);
                return;
            }
            cout << "\n\tEnter a house's ID to unlist it: ";
            int houseId;
            if (!readInt(houseId) || houseId != curMember.listedHouseId){
                cout << "\n\tInvalid house ID. Return back...\n";
                delay(1500);
                return;
            };
            vector <string> labels = {"ID", "Comment", "Score", "Occupier"};
            TableFormatter table(labels);
            for (House house: houseList){
                if (!house.isListed) continue;
                if (house.id == houseId){
                    for (int reviewID : house.reviewId){
                        vector <string> row = houseReviewList[reviewID].toStringArray();
                        row.push_back(memberList[houseReviewList[reviewID].occupiedPersonId].fullName);
                        table.addRow(row);
                    }
                    break;
                }
            }
            table.display("\t");
            waitUntilKeyPressed("\t");
        }
        
        friend class MainMenu;
};