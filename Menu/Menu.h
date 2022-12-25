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
using namespace std;

class Menu{
    private:
        vector<Option> options;

    public:

        void addOption(Option option){
            options.push_back(option);
        }

        void displayOptions(){
            Option temp;
            TableFormatter table = TableFormatter(temp.getFields());
            for(Option option : options){
                table.addRow(option.toStringArray());
            }
            table.display();
        }

        void welcome(){
            cout << "\nEEET2482/COSC2082 ASSIGNMENT\nVACATION HOUSE EXCHANGE APPLICATION\n\nInstructors: Mr. Linh Tran & Phong Ngo\nGroup: \ns3924577, Nguyen Nguyen Khuong\ns3931605, Nguyen Cuong Anh Minh\ns3880115, Nguyen Chau Loan\ns3878280, Min Chi Gia Khiem\n";
        }

        void run(){
            welcome();
            while (true) {
                displayOptions();
                string input = "";
                cout << "Enter an option: ";
                do {
                    getline(cin, input);
                }
                while (input == "");
                for (Option option : options) {
                    if (option.getToggleKey() == input) {
                        option.execute();
                    }
                }
            }
        }
};

void hello(){
    cout << "Hello" << "\n";
}