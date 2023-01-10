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
#include "Menu.h"
#include "../TableFormatter/TableFormatter.h"
#include "../utils/Delay.h"
using namespace std;

class AdminMenu : public Menu{
    public: 
        AdminMenu(vector<House> houseList = {}, vector<Member> memberList = {}, vector<HouseReview> houseReviewList = {}, vector<MemberReview> memberReviewList = {}, vector<Request> requestList = {})
        :Menu({}, houseList, memberList, houseReviewList, memberReviewList, requestList){
            this->addOption(Option("1", "View all members", [&]() -> void {viewAllMembers();}));
            this->addOption(Option("2", "View all houses", [&]() -> void {viewAllHouses();}));
            this->addOption(Option("3", "Return to main menu"));
            this->addOption(Option("4", "Exit the program", [&]() -> void {stop();}));
        }

        void viewAllMembers(string prefix = ""){
            vector <string> labels = {"ID", "Username", "Password", "Full Name", "Phone Number", "Credit Points"};
            TableFormatter table(labels);
            for(Member member: memberList){
                table.addRow(member.toStringArray(true));
            }
            table.display("\t");
            waitUntilKeyPressed("\t");
        }

        void viewAllHouses(string prefix = ""){
            vector <string> labels = {"ID", "Location", "Description", "Available Time Start", "Available Time End", "Consuming Points (per hour)", "Minimum Score Required"};
            TableFormatter table(labels);
            for(House house: houseList){
                table.addRow(house.toStringArray());
            }
            table.display("\t");
            waitUntilKeyPressed("\t");
        }
};
