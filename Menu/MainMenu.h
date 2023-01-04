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
            this->addOption(Option("1", "Guest"));
            this->addOption(Option("2", "Member"));
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

        void run(){
            Menu::welcome();
            RepoService repo;
            houseList = repo.readHouseList();
            memberList = repo.readMemberList();
            memberReviewList = repo.readMemberReviewList();
            houseReviewList = repo.readHouseReviewList();
            requestList = repo.readRequestList();
            while (true) {
                cout << "Use the app as: \n";
                displayOptions();
                string input = "";
                cout << "Enter an option: ";
                do {
                    getline(cin, input);
                }
                while (input == "");
                for (Option option : options) {
                    if (option.getToggleKey() == input) {
                        option.execute();
                    }
                }
            }
        }

        void useApplicationAsGuest(){
            GuestMenu guestMenu(houseList, memberList, houseReviewList, memberReviewList, requestList);
        }
};