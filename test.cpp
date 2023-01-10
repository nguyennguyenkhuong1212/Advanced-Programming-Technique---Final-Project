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
#include "utils/Split.h"
#include "DateService/Date.h"
using namespace std;

void hello(){
    cout << "Hello World!" << endl;
}

int main(){

    MainMenu menu;
    menu.run();

    return 0;
}