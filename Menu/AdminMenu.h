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
using namespace std;

class AdminMenu : public Menu{
    AdminMenu(){
        this->addOption(Option("1", "View all members"));
        this->addOption(Option("2", "View all houses"));
    }
};