#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <functional>
#include <algorithm>
#include "../utils/Delimiter.h"
#pragma once
using namespace std;

class TableFormatter {
    private:
        int spaceBetween = 6;
        vector<string> labels;
        vector<vector<string> > rows;
        vector<int> maxLengthOfColumn;

    public:
        TableFormatter(vector<string> labels)
        : labels(labels){};

        void addRow(vector<string> row){
            rows.push_back(row);
        }

        vector<vector<string> > getRows(){
            return rows;
        }

        void setMaxLengthOfColumn(){
            int maxLen = 0;
            for(int i = 0; i < labels.size(); i++){
                int curLabelLen = labels[i].size();
                maxLen = max(maxLen, curLabelLen);
                for (vector<string> row: rows){
                    int curLen = row[i].size();
                    maxLen = max(maxLen, curLen);
                }
                maxLengthOfColumn.push_back(maxLen);
                maxLen = 0;
            }
        }

        void printTableRow(){
            printDelimiter();
            for(int i = 0; i < labels.size(); i++){
                if (i == 0){
                    cout << labels[i];
                    continue;
                }
                int distance = maxLengthOfColumn[i - 1] 
                               - labels[i - 1].size() 
                               + spaceBetween 
                               + labels[i].length();
                cout << setw(distance) << labels[i];
            }
            cout << endl;
            printDelimiter();
            for(int i = 0; i < rows.size(); i++){
                for(int j = 0; j < rows[i].size(); j++){
                    int distance = 0;
                    if (j != 0) {
                        distance = maxLengthOfColumn[j - 1]
                                   - rows[i][j - 1].length()
                                   + spaceBetween
                                   + rows[i][j].length();
                        cout << setw(distance) << rows[i][j];
                    } else {
                        cout << rows[i][j];
                    }
                }
                if (i != rows.size() - 1) {
                    cout << endl;
                    printDelimiter();
                } else {
                    cout << endl;
                }
            }
        }

        void display(){
            setMaxLengthOfColumn();
            printTableRow();
            printDelimiter();
        }
};