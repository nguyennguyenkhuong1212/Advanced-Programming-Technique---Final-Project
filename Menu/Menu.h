#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <functional>
#include <stdio.h> 
#include "../utils/Option.h"
#include "../TableFormatter/TableFormatter.h"
#include "../utils/Delimiter.h"
#include "../utils/Delay.h"
#include "../HouseService/HouseService.h"
#include "../MemberService/MemberService.h"
#include "../RequestService/RequestService.h"
#include "../RepoService/RepoService.h"
using namespace std;

void endProgram(){
    exit(0);
}

class Menu{
    private:
        vector<Option> options;
        vector<House> houseList;
        vector<Member> memberList;
        vector<HouseReview> houseReviewList;
        vector<MemberReview> memberReviewList;
        vector<Request> requestList;

    public:
        Menu(vector<Option> options = {}, vector<House> houseList = {}, vector<Member> memberList = {}, vector<HouseReview> houseReviewList = {}, vector<MemberReview> memberReviewList = {}, vector<Request> requestList = {})
        :options(options), houseList(houseList), memberList(memberList), houseReviewList(houseReviewList), memberReviewList(memberReviewList), requestList(requestList){}; 

        void addOption(Option option){
            options.push_back(option);
        }

        void displayOptions(){
            Option temp;
            TableFormatter table(temp.getFields());
            for(Option option : options){
                table.addRow(option.toStringArray());
            }
            table.display();
        }

        void welcome(){
            cout << "\nEEET2482/COSC2082 ASSIGNMENT\nVACATION HOUSE EXCHANGE APPLICATION\n\nInstructors: Mr. Linh Tran & Phong Ngo\nGroup: \ns3924577, Nguyen Nguyen Khuong\ns3931605, Nguyen Cuong Anh Minh\ns3880115, Nguyen Chau Loan\ns3878280, Min Chi Gia Khiem\n";
        }

        void run(string endMenuKey = "X"){
            while (true) {
                welcome();
                displayOptions();
                string input = "";
                cout << "\nEnter an option: ";
                do {
                    getline(cin, input);
                }
                while (input == "");
                if (input == "X") continue;
                if (input == endMenuKey) break;
                bool foundOption = false;
                for (Option option : options) {
                    if (option.getToggleKey() == input) {
                        option.execute();
                        foundOption = true;
                        break;
                    }
                }
                if (!foundOption) {
                    cout << "Invalid option. Please enter again.\n\n";
                }
            }
        }

        void stop(){
            RepoService repo;
            cout << "Exiting...\n";
            repo.writeMemberListIntoFile(memberList, false);
            repo.writeHouseListIntoFile(houseList, false);
            repo.writeMemberReviewListIntoFile(memberReviewList, false);
            repo.writeRequestListIntoFile(requestList, false);
            repo.writeHouseReviewListIntoFile(houseReviewList, false);
            exit(0);
        }

        void viewAllOccupiers(House house, string prefix = ""){
            if (house.occupierId.size() == 0) {
                return;
            }
            vector <string> labels = {"ID", "Username", "Full Name"};
            TableFormatter table(labels);
            for(int id: house.occupierId){
                Member res;
                if (findMemberById(id, memberList, res)){
                    table.addRow(res.toStringArray());
                }
            }
            table.display("\t");
        }

        void viewAllHouse(Member member, string prefix = ""){ // Use only for members
            if (member.listedHouseId == -1){
                cout << "\n\tYou listed no house. Returning back...\n";
                delay(1500);
                return;
            }
            vector <string> labels = {"ID", "Location", "Description", "Available Time Start", "Available Time End", "Consuming Points (per hour)", "Minimum Score Required"};
            TableFormatter table(labels);
            House res;
            if (findHouseById(member.listedHouseId, houseList, res)) {
                table.addRow(res.toStringArray());
            }
            table.display("\t");
        }

        bool viewAllHouseListed(Member member, string prefix = ""){ // Use only for members
            vector <string> labels = {"ID", "Location", "Description", "Available Time Start", "Available Time End", "Consuming Points (per hour)", "Minimum Score Required"};
            TableFormatter table(labels);
            House res;
            if (findHouseById(member.listedHouseId, houseList, res)) {
                if (res.isListed) {
                    table.addRow(res.toStringArray());
                }
            }
            table.display(prefix);
            return true;
        }

        bool viewAllHouseOccupied(Member member, string prefix = ""){ // Use only for members
            vector <string> labels = {"ID", "Location", "Description", "Available Time Start", "Available Time End", "Consuming Points (per hour)", "Minimum Score Required"};
            TableFormatter table(labels);
            bool found = false;
            House res;
            for (int houseId: member.occupiedHouseId){
                if (findHouseById(houseId, houseList, res)) {
                    found = true;
                    table.addRow(res.toStringArray());
                }
            }
            if (found == false){
                cout << "\n" << prefix << "You occupied no house.\n";
                return false;
            }
            return true;
            double sum = 0;
            double i = 0;
            for (int id: member.reviewId){
                for (MemberReview memberReview: memberReviewList){
                    if (memberReview.id == id){
                        sum += memberReview.score;
                        i++;
                        continue;
                    }
                }
            }
            if (i == 0) return 10;
            return (sum / i);
        }

        friend class MainMenu;
        friend class GuestMenu;
        friend class MemberMenu;
        friend class AdminMenu;
};