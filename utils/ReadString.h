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
using namespace std;

void readString(string& st){
    string temp = "";
    do {
        getline(cin, temp);
    }
    while (temp == "");
    st = temp;
}