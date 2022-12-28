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

class AdminMenu : public Menu{
    AdminMenu(){
        this->addOption(Option("1", "Login with your predefined username and password"));
        this->addOption(Option("2", "View all members"));
        this->addOption(Option("3", "View all houses"));
    }
};