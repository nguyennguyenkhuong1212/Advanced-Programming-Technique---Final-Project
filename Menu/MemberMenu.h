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
#pragma once
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
            this->addOption(Option("5", "Request to occupy a house"));
            this->addOption(Option("6", "View all requests to your listed house"));
            this->addOption(Option("7", "Accept a request to your listed house and reject all the others"));
            this->addOption(Option("8", "Occupy a successfully requested house"));
            this->addOption(Option("9", "Rate for your occupied house"));
            this->addOption(Option("10", "Rate occupiers who had used your house", [&]() -> void {rateOccupier();}));
            this->addOption(Option("11", "Return to main menu"));
            this->addOption(Option("12", "Exit the program", [&]() -> void {stop();}));
        }

        void viewInformation(){
            vector <string> labels = {"ID", "Username", "Password", "Full Name", "Phone Number", "Credit Points"};
            TableFormatter table(labels);
            table.addRow(curMember.toStringArray(true));
            table.display();
            waitUntilKeyPressed();
        }

        void listHouse(){
            string location;
            string description;
            string availableTimeStart;
            string availableTimeEnd;
            int consumingPoints;
            double minimumRating;
            
            cout << "Enter location: ";
            readString(location);
            cout << "Enter description: ";
            readString(description);
            cout << "Available from: ";
            readString(availableTimeStart);
            cout << "Available until: ";
            readString(availableTimeEnd);
            cout << "Enter consuming points to occupy: ";
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
                    memberList[i].listedHouseId.push_back(id);
                    break;
                }
            }
            houseList.push_back(tempHouse);
            waitUntilKeyPressed();
        }

        void unlistHouse(){
            if (curMember.listedHouseId.size() == 0){
                cout << "\n\tYou have no house. Returning back...\n";
                delay(1500);
                return;
            }
            cout << "\n\tThis is all your listed house:\n";
            if (!viewAllHouseListed(curMember, "\t")) {
                waitUntilKeyPressed("\t");
                return;
            }
            cout << "\n\tEnter a house's ID to unlist it: ";
            int houseId;
            if (!readInt(houseId)){
                cout << "\n\tInvalid house ID. Return back...\n";
                delay(1500);
                return;
            };
            bool found = false;
            for (int i = 0; i < houseList.size(); i++) {
                if (houseList[i].isListed == false) continue;
                if (houseList[i].id == houseId){
                    houseList[i].isListed = false;
                    found = true;
                }
            }
            if (!found){
                cout << "\n\tCannot found this house. Returning back...\n";
                delay(1500);
                return;
            }
            waitUntilKeyPressed("\t");
        }

        void searchForAllAvailableAndSuitableHouseInACity(){
            vector <string> labels = {"ID", "Location", "Description", "Available Time Start", "Available Time End", "Consuming Points", "Minimum Score Required"};
            TableFormatter table(labels);
            string location;
            cout << "Enter location: ";
            readString(location); 
            bool found = false;
            for (House house: houseList){
                if (house.location == location && house.consumingPoints <= curMember.creditPoint && house.isListed && find(curMember.listedHouseId.begin(), curMember.listedHouseId.end(), house.id) == curMember.listedHouseId.end() && getScore(curMember) >= house.minimumRating){
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
            waitUntilKeyPressed();
        };

        void rateOccupier(){
            cout << "\n\tThis is all your listed house:\n";
            if (curMember.listedHouseId.size() == 0){
                cout << "\n\tYou have no house. Returning back...\n";
                delay(1500);
                return;
            }
            viewAllHouse(curMember, "\t\t");
            cout << "\n\tEnter a house's ID to view all the occupiers: ";
            int houseId;
            if (!readInt(houseId)){
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
            MemberReview review(memberReviewList.size(), comment, score, houseId, occupierId);
            memberReviewList.push_back(review);
            cout << "\n";
            delay(1500);
        }

        friend class MainMenu;
};