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
            this->addOption(Option("2", "List a house"));
            this->addOption(Option("3", "Unlist a house"));
            this->addOption(Option("4", "Search for all available and suitable houses in a city"));
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

        void rateOccupier(){
            cout << "\n\tThis is all your listed house:\n";
            viewAllHouseListed(curMember, "\t\t");
            cout << "\n\tEnter a house's ID to view all the occupiers: ";
            int houseId;
            cin >> houseId;
            cout << "\n\tThis is all of people who occupied this house:\n";
            for (House house: houseList){
                if (house.id == houseId){
                    viewAllOccupiers(house, "\t\t");
                    break;
                }
            }
            cout << "\n\tEnter the occupier's ID that you want to rate: ";
            int occupierId;
            cin >> occupierId;
            cout << "\tEnter the score for this occupier: ";
            int score;
            cin >> score;
            cout << "\tEnter the comment for this occupier: ";
            string comment;
            readString(comment);
            MemberReview review(memberReviewList.size(), comment, score, houseId, occupierId);
            memberReviewList.push_back(review);
            cout << "\n";
            delay(1000);
        }

        friend class MainMenu;
};