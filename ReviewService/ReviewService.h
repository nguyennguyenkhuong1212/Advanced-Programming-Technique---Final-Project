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

class Review{
    private:
        string comment;
        int score;

    public: 
        Review(string comment = "", int score = 0)
        : comment(comment), score(score){};    

        void addReview(){
            cout << "Enter score: ";
            cin >> score;
            cout << "Enter comment: ";
            cin >> comment;
        }

        friend class HouseReview;
        friend class MemberReview;
};