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
#include "GuestMenu.h"
#include "MemberMenu.h"
#include "AdminMenu.h"
#include "../RepoService/RepoService.h"
#include "../utils/Delay.h"

using namespace std;

class MainMenu : public Menu {
    public:
        MainMenu(){
            this->addOption(Option("1", "Guest", [&]() -> void{useApplicationAsGuest();}));
            this->addOption(Option("2", "Member", [&]() -> void{useApplicationAsMember();}));
            this->addOption(Option("3", "Admin", [&]() -> void{useApplicationAsAdmin();}));
        }

        void displayOptions(){
            Option temp;
            const vector <string> fields = {"Input", "Role"};
            TableFormatter table(fields);
            for(Option option : options){
                table.addRow(option.toStringArray());
            }
            table.display();
        }

        void run(string endMenuKey = "4"){
            RepoService repo;
            houseList = repo.readHouseList();
            memberList = repo.readMemberList();
            memberReviewList = repo.readMemberReviewList();
            houseReviewList = repo.readHouseReviewList();
            requestList = repo.readRequestList();
            while (true) {
                welcome();
                cout << "Use the app as: \n";
                displayOptions();
                cout << "\nYour could also exit the application by enter 4 !!!\n\n";
                string input = "";
                cout << "Enter your choice: ";
                do {
                    getline(cin, input);
                }
                while (input == "");
                if (input == endMenuKey) stop();
                for (Option option : options) {
                    if (option.getToggleKey() == input) {
                        option.execute();
                    }
                }
            }
        }

        void useApplicationAsGuest(){
            GuestMenu guestMenu(houseList, memberList, houseReviewList, memberReviewList, requestList);
            guestMenu.run("3");
            houseList = guestMenu.houseList;
            memberList = guestMenu.memberList;
            houseReviewList = guestMenu.houseReviewList;
            memberReviewList = guestMenu.memberReviewList;
            requestList = guestMenu.requestList;
        }

        void useApplicationAsMember(){
            string username;
            string password;
            cout << "Enter username: ";
            readString(username);
            cout << "Enter password: ";
            readString(password);
            bool accountExisted = false;
            bool wrongPassword = false;
            for (Member member : memberList){
                if (member.username == username){
                    if (member.password != password){
                        wrongPassword = true;
                        break;
                    }
                    MemberMenu memberMenu(houseList, memberList, houseReviewList, memberReviewList, requestList, member);
                    memberMenu.run("14");
                    houseList = memberMenu.houseList;
                    memberList = memberMenu.memberList;
                    houseReviewList = memberMenu.houseReviewList;
                    memberReviewList = memberMenu.memberReviewList;
                    requestList = memberMenu.requestList;
                    accountExisted = true;
                    break;
                }
            }
            if (wrongPassword){
                cout << "\nWrong password. Return back to main menu...\n";
                delay(1500);
                return;
            }
            if (!accountExisted){
                cout << "\nCannot find this user. Return back to main menu...\n";
                delay(1500);
            }
        }

        void useApplicationAsAdmin(){
            string username;
            string password;
            cout << "Enter username: ";
            readString(username);
            cout << "Enter password: ";
            readString(password);
            if (username == "admin"){
                if (password == "admin"){
                    AdminMenu adminMenu(houseList, memberList, houseReviewList, memberReviewList, requestList);
                    adminMenu.run("3");
                    houseList = adminMenu.houseList;
                    memberList = adminMenu.memberList;
                    houseReviewList = adminMenu.houseReviewList;
                    memberReviewList = adminMenu.memberReviewList;
                    requestList = adminMenu.requestList;
                }
                else {
                    cout << "\nWrong password. Return back to main menu...\n";
                    delay(1500);
                    return;
                }
            } 
            else {
                cout << "\nCannot find this user. Return back to main menu...\n";
                delay(1500);
            }
        }
};