#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <functional>
#include "Menu.h"
using namespace std;

class GuestMenu : public Menu{
    public:
        GuestMenu(vector<House> houseList = {}, vector<Member> memberList = {}, vector<HouseReview> houseReviewList = {}, vector<MemberReview> memberReviewList = {}, vector<Request> requestList = {})
        :Menu({}, houseList, memberList, houseReviewList, memberReviewList, requestList){
            this->addOption(Option("1", "Register to become a member", [&]() -> void {signUp();}));
            this->addOption(Option("2", "View all house details (not including reviews and availability)", [&]() -> void {viewAllHouseDetails();}));
            this->addOption(Option("3", "Exit the program", [&]() -> void {Menu::stop();}));
        };

        void signUp(){
            string username;
            string password;
            string fullName;
            string phoneNumber;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            cout << "Enter full name: ";
            cin >> fullName;
            cout << "Enter phone number: ";
            cin >> phoneNumber;
            int id = memberList.size();
            Member member(id, username, password, fullName, phoneNumber);
            memberList.push_back(member);
        }

        void viewAllHouseDetails(){
            cout << "\n";
            int i = 0;
            for (House house : houseList){
                cout << "- House " << ++i << ": " << endl;
                cout << house.toDisplayLine("\t") << "\n";
            }
        }
};