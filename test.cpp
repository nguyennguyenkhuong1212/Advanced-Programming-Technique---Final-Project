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
#pragma once
using namespace std;

void hello(){
    cout << "Hello World!" << endl;
}

int main(){
    MainMenu menu;
    menu.run();
}
