#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <functional>
#include "../utils/Option.h"
#include "../TableFormatter/TableFormatter.h"
#include "../utils/Delimiter.h"
#include "Menu.h"
#pragma once
using namespace std;

class MainMenu : public Menu {
    public:
        MainMenu(){
            this->addOption(Option("1", "Guest"));
            this->addOption(Option("2", "Member"));
            this->addOption(Option("3", "Admin"));
        }
};