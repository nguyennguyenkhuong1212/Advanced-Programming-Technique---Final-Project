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
#include "../utils/ReadString.h"
#include "../utils/ReadInt.h"
#include "../utils/Delay.h"
using namespace std;

class GuestMenu : public Menu{
    public:
        GuestMenu(vector<House> houseList = {}, vector<Member> memberList = {}, vector<HouseReview> houseReviewList = {}, vector<MemberReview> memberReviewList = {}, vector<Request> requestList = {})
        :Menu({}, houseList, memberList, houseReviewList, memberReviewList, requestList){
            this->addOption(Option("1", "Register to become a member", [&]() -> void {signUp();}));
            this->addOption(Option("2", "View all house details (not including reviews and availability)", [&]() -> void {viewAllHouseDetails();}));
            this->addOption(Option("3", "Return to main menu"));
            this->addOption(Option("4", "Exit the program", [&]() -> void {Menu::stop();}));
        };

        void signUp(){
            string username;
            string password;
            string fullName;
            string phoneNumber;
            cout << "Enter username: ";
            readString(username);
            bool accountExists = false;
            for (Member member : memberList){
                if (member.username == username) {
                    accountExists = true;
                    break;
                }
            }
            if (accountExists){
                cout << "\nAccount already exists. Return back...\n";
                delay(1500);
                return;
            }
            cout << "Enter password: ";
            readString(password);
            cout << "Enter full name: ";
            readString(fullName);
            cout << "Enter phone number: ";
            readString(phoneNumber);
            if (!is_number(phoneNumber)){
                cout << "\nPhone number invalid. Return back...\n";
                delay(1500);
                return;
            }
            int id = memberList.size();
            Member member(id, username, password, fullName, phoneNumber);
            memberList.push_back(member);
        }

        void viewAllHouseDetails(){
            cout << "\n";
            int i = 0;
            for (House house : houseList){
                cout << "\t- House " << ++i << ": " << endl;
                cout << house.toDisplayLine("\t\t") << "\n";
            }
        }
};