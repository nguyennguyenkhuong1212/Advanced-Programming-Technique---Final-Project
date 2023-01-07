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
using namespace std;

class MainMenu : public Menu {
    public:
        MainMenu(){
            this->addOption(Option("1", "Guest", [&]() -> void{useApplicationAsGuest();}));
            this->addOption(Option("2", "Member", [&]() -> void{useApplicationAsMember();}));
            this->addOption(Option("3", "Admin"));
        }

        void displayOptions(){
            Option temp;
            const vector <string> fields = {"Input", "Role"};
            TableFormatter table = TableFormatter(fields);
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
                cout << "Enter an option: ";
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
        }

        void useApplicationAsMember(){
            MemberMenu memberMenu(houseList, memberList, houseReviewList, memberReviewList, requestList, memberList[0]);
            memberMenu.run("10");
        }
};