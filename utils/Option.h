#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <functional>
using namespace std;

class Option{   
    private:
        const vector <string> fields = {"Input", "Action"};
        string labelAction;
        string toggleKey;
        function <void()> command;

    public:
        Option(string labelAction = "", string toggleKey = "", function <void()> command = nullptr)
        : labelAction(labelAction), toggleKey(toggleKey), command(command){};
    
        vector <string> getFields(){
            return fields;
        }

        vector <string> toStringArray(){
            vector <string> res;
            res.push_back(toggleKey);
            res.push_back(labelAction);
            return res;
        }

        void execute(){
            command();
        }

        string getLabelAction(){
            return labelAction;
        }

        string getToggleKey(){
            return toggleKey;
        }
};