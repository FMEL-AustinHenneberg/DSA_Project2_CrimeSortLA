#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include "Crime.h"
using namespace std;

int main() {
    // file spec variables
    string fileStr = "../resources/Crime_Data_from_2020_to_2024.csv";
    string colStr;
    int cols = 28;
    int currCol = 0;
    int rcd = 0;
    int area = 0;
    string areaDesc = "";
    int crime = 0;
    string crimeDesc = "";
    // Data handling Variables
    Crime LA;
    map<int, string> areaIDMap;
    map<int, string> crimeIDMap;
    //User option varables
    map<int,string> userOptions = {
        {1, "1. Most Frequent Crimes"},
        {2, "2. Least Frequent Crimes"},
        {3, "3. Crime counts in the LAPD Area"},
        {4, "4. Find top area for a crime"},
        {5, "5. Merge vs. Heap Sort"},
        {6, "6. Exit"}
    };
    // Welcome message
    cout << "Welcome to CrimeSort LA!" << endl;
    // Read file
    ifstream file(fileStr);
    if (!file.is_open()){
        std::cerr << "File failed to open." << std::endl;
    }
    int col = 0;
    int linesNum = 0;
    if (file.is_open()) {
        //get rid of header
        getline(file,colStr);
        while (!file.eof()) {
            getline(file,colStr,',');
            col++;
            currCol = col%cols;
            //only get columns we care about
            if (currCol == 1 && colStr != "") { // crime record id
                rcd = stoi(colStr);
            }
            else if (currCol == 5) { // crime area id
                area = stoi(colStr);
            }
            else if (currCol == 6) { // crime area description
                areaDesc = colStr;
            }
            else if (currCol == 9) {
                crime = stoi(colStr);
            }
            else if (currCol == 10) {
                crimeDesc = colStr;
            }
            // read rest of line and process end of line logic
            else if (currCol > 10) {
                // create and insert record
                LA.insertRecord(rcd, area, crime);
                // Insert map records for later reporting
                areaIDMap.insert({area,areaDesc});
                crimeIDMap.insert({crime,crimeDesc});
                // get rest of line to discard
                getline(file,colStr);
                // reset column counter
                col = 0;
                // increment line count
                linesNum++;
            }
        }
    }
    int userChoice = -1;
    // user interaction screen
    cout << linesNum << " Records Loaded." << endl << endl;
    for (auto it = userOptions.begin(); it != userOptions.end(); ++it) {
        cout << it->second << endl;
    }
    // get choice and determine if it is valid.
    bool choiceValid = false;
    while (!choiceValid) {
        cout << endl << "Enter Choice: ";
        cin >> userChoice;
        if (userOptions.find(userChoice) != userOptions.end()) {
            cout << "Correct choice!" << endl;
            choiceValid = true;
        }
        else {
            cout << "Incorrect choice, try again." << endl;
        }
    }
    // Use choice to determine next step
    if (userChoice == 1) {
        //get most frequent crimes
    }
    else if (userChoice == 2) {
        //get least frequent crimes
    }
    else if (userChoice == 3) {
        //get Crime counts
    }
    else if (userChoice == 4) {
        //get area with most crime
    }
    else if (userChoice == 5) {
        // Test and Verify Merge vs Heap Sort
    }
    else if (userChoice == 6) {
        cout << "Have a good one!" << endl;
    }
    return 0;
}