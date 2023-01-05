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
#include "Menu/MainMenu.h"
#include "Menu/GuestMenu.h"
#include "MemberService/MemberService.h"
#include "HouseService/HouseService.h"
#include "RepoService/RepoService.h"
using namespace std;

void hello(){
    cout << "Hello World!" << endl;
}

int main(){
    // MainMenu menu;
    // menu.run();
    // Member m1(1, "khuongproha", "Hello123", "Nguyen Nguyen Khuong", "0865122487", 500, {1, 2, 3}, {1});
    // ofstream dataFile;
    // dataFile.open("RepoService/MemberList.csv", ios::out);
    // dataFile << m1.toDataLine();
    // dataFile.close();
    // RepoService repo;
    // vector<Member> memberList = repo.readMemberList();
    // for (Member member : memberList){
    //     cout << member.toDataLine() << endl;
    // }
    

    // House h1(1, "Ho Chi Minh City", "Big house", "31/12/2022", "01/02/2023", {1});
    // dataFile.open("RepoService/HouseList.csv", ios::out);
    // dataFile << h1.toDataLine();
    // dataFile.close();
    // vector<House> houseList = repo.readHouseList();
    // for (House house : houseList){
    //     cout << house.toDataLine() << endl;
    // }

    MainMenu menu;
    menu.run();

    return 0;
}


