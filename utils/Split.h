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

vector<string> split(string st, char sep) {
    vector<string> res = {};
    string temp = "";
    for(int i = 0; i < st.length(); i++){
        if(st[i] != sep) {
            temp += st[i];
        }
        else {
            res.push_back(temp);
            temp = "";
        }
    }
    if (temp != "") {
        res.push_back(temp);
    }
    return res;
}