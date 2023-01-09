#ifndef __READINT
#define __READINT
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
#include "ReadString.h"
using namespace std;

bool is_number(const string& s)
{
    return !s.empty() && find_if(s.begin(), s.end(), [](unsigned char c) { return !isdigit(c); }) == s.end();
}

bool readInt(int& num){
    string temp;
    readString(temp);
    if (!is_number(temp)){
        return false;
    }
    num = stoi(temp);
    return true;
}

#endif