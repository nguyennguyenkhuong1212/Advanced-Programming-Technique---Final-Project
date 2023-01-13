#ifndef DATE_H
#define DATE_H
#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <functional>
#include <algorithm>
#define _GNU_SOURCE 
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../utils/ReadInt.h"
#include "../utils/Split.h"
using namespace std;

string formatYear(int year){
    string res = to_string(year);
    for (int i = 0; i < 4-res.size(); i++)
    {
        res = "0" + res;
    }
    return res;
}

string formatTime(int time){
    string res = to_string(time);
    if (time < 10) res = "0" + res;
    return res;
}

class Date{
    public:
        int day;
        int month;
        int year;
        int hour;
        int minute;

        Date(){};

        Date(int day, int month, int year, int hour, int minute)
        : day(day), month(month), year(year), hour(hour), minute(minute){};

        string toDisplayLine(){
            stringstream ss;
            ss << formatTime(day) << "/" << formatTime(month) << "/" << formatYear(year) << " " << formatTime(hour) << ":" << formatTime(minute);
            return ss.str();
        }

        string toDataLine(){
            stringstream ss;
            ss << formatYear(year) << "/" << formatTime(month) << "/" << formatTime(day) << " " << formatTime(hour) << ":" << formatTime(minute) << ":" << "00";
            return ss.str();
        }
};

bool operator < (const Date& date1, const Date& date2){
    if (date1.year != date2.year) {return date1.year < date2.year;}
    if (date1.month != date2.month) {return date1.month < date2.month;}
    if (date1.day != date2.day) {return date1.day < date2.day;}
    if (date1.hour != date2.hour) {return date1.hour < date2.hour;}
    return (date1.minute < date2.minute);
}

bool operator == (const Date& date1, const Date& date2){
    return (date1.day == date2.day) && (date1.month == date2.month) && (date1.year == date2.year) && (date1.hour == date2.hour) && (date1.minute == date2.minute);
}

bool operator <= (const Date& date1, const Date& date2){
    return (date1 < date2 || date1 == date2);
}

bool operator > (const Date& date1, const Date& date2){
    return (!(date1 <= date2));
}

bool operator >= (const Date& date1, const Date& date2){
    return (!(date1 < date2));
}

double calDifference(Date date1, Date date2){
    char *time1 = new char[date1.toDataLine().size() + 1];
    char *time2 = new char[date2.toDataLine().size() + 1];
    strcpy(time1, date1.toDataLine().c_str());
    strcpy(time2, date2.toDataLine().c_str());
    const char *ctime1 = time1;
    const char *ctime2 = time2;

    struct tm tm1, tm2;
    time_t t1, t2;

    istringstream ss1(ctime1);
    istringstream ss2(ctime2);

    ss1 >> get_time(&tm1, "%Y/%m/%d %T");
    ss2 >> get_time(&tm2, "%Y/%m/%d %T");

    t1 = mktime(&tm1);   
    t2 = mktime(&tm2);

    if (date1 > date2) return difftime(t1, t2)/60/60;
    return difftime(t2, t1)/60/60;
}

bool checkInvalidYear(int day, int month, int year){
    if (1000 <= year && year <= 3000)
    {
        if((month==1 || month==3 || month==5|| month==7|| month==8||month==10||month==12) && day>0 && day<=31) return true;
        if(month==4 || month==6 || month==9|| month==11 && day>0 && day<=30) return true;
        if(month==2){
            if((year%400==0 || (year%100!=0 && year%4==0)) && day>0 && day<=29) return true;
            if(day>0 && day<=28) return true;
            return false;
        }
        return false;
    }
    return false;
}

bool readDate(Date &date, string prefix = ""){
    int day;
    int month;
    int year;
    int hour;
    int minute;

    cout << prefix << "Enter day: ";
    if (!readInt(day)){
        cout << "\n" << prefix << "Invalid input. Return back...\n";
        return false;
    }

    cout << prefix << "Enter month: ";
    if (!readInt(month)){
        cout << "\n" << prefix << "Invalid input. Return back...\n";
        return false;
    }

    cout << prefix << "Enter year: ";
    if (!readInt(year)){
        cout << "\n" << prefix << "Invalid input. Return back...\n";
        return false;
    }

    if (!checkInvalidYear(day, month, year)){
        cout << "\n" << prefix << "Date not existed. Return back...\n";
        return false;
    }
    
    cout << prefix << "Enter hour: ";
    if (!readInt(hour) || hour < 0 || hour > 23){
        cout << "\n" << prefix << "Invalid input. Return back...\n";
        return false;
    }

    cout << prefix << "Enter minute: ";
    if (!readInt(minute) || minute < 0 || minute > 59){
        cout << "\n" << prefix << "Invalid input. Return back...\n";
        return false;
    }
    Date newDate(day, month, year, hour, minute);
    date = newDate;
    return true;
}

Date getDatefromDatabase(vector <string> dataLine){
    vector <string> date = split(dataLine[0], '/');
    vector <string> time = split(dataLine[1], ':');
    Date newDate(stoi(date[2]), stoi(date[1]), stoi(date[0]), stoi(time[0]), stoi(time[1]));
    return newDate;
}

#endif