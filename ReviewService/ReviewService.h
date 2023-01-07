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
#include "../utils/ReadString.h"
using namespace std;

class Review{
    private:
        int id;
        string comment;
        int score;

    public: 
        Review(int id = 0, string comment = "", int score = 0)
        : id(id), comment(comment), score(score){};    

        void addReview(){
            cout << "Enter score: ";
            cin >> score;
            cout << "Enter comment: ";
            readString(comment);
        }

        friend class HouseReview;
        friend class MemberReview;
};