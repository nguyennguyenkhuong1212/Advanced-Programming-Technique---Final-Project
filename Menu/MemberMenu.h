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

class MemberMenu : public Menu{
    MemberMenu(){
        this->addOption(Option("1", "Login with your account"));
        this->addOption(Option("2", "List a house"));
        this->addOption(Option("3", "Unlist a house"));
        this->addOption(Option("4", "Search for all available and suitable houses in a city"));
        this->addOption(Option("5", "Request to occupy a house"));
        this->addOption(Option("6", "View all requests to your listed house"));
        this->addOption(Option("7", "Accept a request to your listed house and reject all the others"));
        this->addOption(Option("8", "Occupy a successfully requested house"));
        this->addOption(Option("9", "Rate for your occupied house"));
        this->addOption(Option("10", "Rate occupiers who had used your house"));
    }
};