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
#pragma once
using namespace std;

class GuestMenu : public Menu{
    GuestMenu(){
        this->addOption(Option("1", "Register to become a member"));
        this->addOption(Option("2", "View all house details (not including reviews and availability"));
    }
};