#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <regex>
#include "Crime.h"
#include "HeapSort.h"
#include "MergeSort.h"

using namespace std;

bool PrintMostOrLeast(vector<pair<int,int>> data, map<int, string> IDMap, bool hi, int amt) {
    int s = data.size();
    if (amt > s) {
        cout << "Amount is too large, try a different value.";
        return false;
    }
    //highest
    if (hi == 1) {
        for (int i = s-1; i >= s-amt; i--) {
            cout << IDMap[data[i].first] << ": " << data[i].second << " times" << endl;
        }
    }
    //lowest
    if (hi == 0) {
        for (int i = 0; i < amt; i++) {
            cout << IDMap[data[i].first] << ": " << data[i].second << " times" << endl;
        }
    }
    return true;
}
bool VerifyAndReportSort(vector<pair<int,int>> hSort, vector<pair<int,int>> mSort, int heapTime, int mergeTime) {
    string notValidMsg = "Sorting methods are not valid.";
    //verify both sort vectors are the same size before proceeding.
    cout << "Heap Sort: " << hSort.size() << " records" << endl;
    cout << "Merge Sort: " << mSort.size() << " records" << endl;

    if (hSort.size() != mSort.size()) {
        cout << notValidMsg << " Methods vary in size." << endl;
        return false;
    }
    for (int i = 0; i < hSort.size(); i++) {
        if (hSort[i].second != mSort[i].second) {
            cout << notValidMsg << " Methods vary in sort." << endl;
            return false;
        }
    }
    //Methods resulted in the same record count and record sort
    cout << "Both methods resulted in the same record count and values." << endl;
    cout << "Execution time for Heap Sort: " << heapTime << " microseconds" << endl;
    cout << "Execution time for Merge Sort:" << mergeTime << " microseconds" << endl;
    string fastSort = "";
    string slowSort = "";
    float faster = 0.0;

    if (heapTime < mergeTime) {
        fastSort = "Heap Sort"; slowSort = "Merge Sort";
        faster = float(mergeTime) / float(heapTime);
    }
    else {
        fastSort = "Merge Sort"; slowSort = "Heap Sort";
        faster = float(heapTime) / float(mergeTime);
    }
    cout << fastSort << " was " << faster << "x faster than " << slowSort << endl;
    return true;
}
int SortAndMeasure(vector<pair<int,int>>& data, bool heap) {
    auto t1 = std::chrono::system_clock::now();
    if (heap) {
        heapSort(data);
    }
    else {
        mergeSort(data);
    }
    auto t2 = std::chrono::system_clock::now();
    auto t3 = t2-t1;
    return t3.count();
}
void PrintOptions(map<int,string> options) {
    for (auto it = options.begin(); it != options.end(); ++it) {
        cout << it->second << endl;
    }
}
int ConvertToInt(string input) {
    try {
        int i  = stoi(input);
        return i;
    }
    catch (...) {
        return -1;
    }
}
bool GetAndValidateCount(int& intCount, string areaOrCrime) {
    string count = "";
    cout << "How many " << areaOrCrime << " would you like to display?\t";
    cin >> count;
    intCount = ConvertToInt(count);
    if (intCount == -1) {
        cout << "Incorrect choice, try again." << endl;
        return false;
    }
    else {
        return true;
    }
}

int main() {
    regex quote_re("\""); // regex quote
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
        {1, "1. Find Most Frequent Crimes"},
        {2, "2. Find Least Frequent Crimes"},
        {3, "3. Get all Crime counts by Crime Category."},
        {4, "4. Find Areas with the most amount of crime."},
        {5, "5. Find Areas with the least amount of crime."},
        {6, "6. Get all Crime counts by Area."},
        {7, "7. Merge vs. Heap Sort"},
        {8, "8. Exit"}
    };
    // Welcome message
    cout << "Welcome to CrimeSort LA!" << endl;
    cout << "Loading Records..." << flush;
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
                areaDesc = regex_replace(colStr, quote_re, "");
            }
            else if (currCol == 9) {
                crime = stoi(colStr);
            }
            else if (currCol == 10) {
                crimeDesc = regex_replace(colStr, quote_re, "");
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
    cout << linesNum << " Records Loaded." << endl;
    cout << "Sorting data and measuring performance..." << flush;

    // Replicate data for sort comparison
    vector<pair<int,int>> heapAreas = LA.getAreas();
    vector<pair<int,int>> mergeAreas = LA.getAreas();
    vector<pair<int,int>> heapCrime = LA.getCrimes();
    vector<pair<int,int>> mergeCrime = LA.getCrimes();

    // Get sorting times for each sorting method and dataset
    int heapAreaT = SortAndMeasure(heapAreas,true);
    int mergeAreaT = SortAndMeasure(mergeAreas,false);
    int heapCrimeT = SortAndMeasure(heapCrime,true);
    int mergeCrimeT = SortAndMeasure(mergeCrime,false);

    //count by crime and areas
    auto crimeCount = countByCrime(LA.getRecords());
    auto areaCount = countByArea(LA.getRecords());

    //sort crime and areas
    heapSort(crimeCount);
    heapSort(areaCount);

    cout << "Complete!" << endl;

    //User input variables
    string userChoiceMenu = "";
    int intChoice = -1;
    int intCount = -1;
    // get choice and determine if it is valid.
    bool choiceMenuValid = false;
    bool choiceCountValid = false;
    bool exit = false;
    // user interaction screen
    do {
        // print user options
        cout << "Please choose one of the following:" << endl << endl;
        PrintOptions(userOptions);
        //menu choice validation
        while (!choiceMenuValid) {
            cout << endl << "Enter Choice: ";
            cin >> userChoiceMenu;
            intChoice = ConvertToInt(userChoiceMenu);
            if (userOptions.find(intChoice) != userOptions.end()) {
                choiceMenuValid = true;
            }
            else {
                cout << "Incorrect choice, try again." << endl;
            }
        }
        // Use choice to determine next step
        if (intChoice == 1) {
            while (!choiceCountValid) {
                choiceCountValid = GetAndValidateCount(intCount,"crimes");
            }
            bool success = false;
            while (!success) {
                cout << "Top " << intCount << " most frequent Crimes:" << endl;
                success = PrintMostOrLeast(crimeCount, crimeIDMap, true, intCount);
                cout << "Press any key and enter to return to menu." << endl;
                cin >> userChoiceMenu;
            }
        }
        //get least frequent crimes
        else if (intChoice == 2) {
            while (!choiceCountValid) {
                choiceCountValid = GetAndValidateCount(intCount,"crimes");
            }
            bool success = false;
            while (!success) {
                success = PrintMostOrLeast(crimeCount, crimeIDMap, false, intCount);
                cout << "Press any key and enter to return to menu." << endl;
                cin >> userChoiceMenu;
            }
        }
        // print all crime counts
        else if (intChoice == 3) {
            cout << "All crime counts by Crime Category:" << endl;
            PrintMostOrLeast(crimeCount, crimeIDMap, true, crimeCount.size());
            cout << "Press any key and enter to return to menu." << endl;
            cin >> userChoiceMenu;
        }
        // print areas with most crime
        else if (intChoice == 4) {
            while (!choiceCountValid) {
                choiceCountValid = GetAndValidateCount(intCount,"areas");
            }
            bool success = false;
            while (!success) {
                success = PrintMostOrLeast(areaCount, areaIDMap, true, intCount);
                cout << "Press any key and enter to return to menu." << endl;
                cin >> userChoiceMenu;
            }
        }
        //print areas with least crime
        else if (intChoice == 5) {
            while (!choiceCountValid) {
                choiceCountValid = GetAndValidateCount(intCount,"areas");
            }
            bool success = false;
            while (!success) {
                success = PrintMostOrLeast(areaCount, areaIDMap, false, intCount);
                cout << "Press any key and enter to return to menu." << endl;
                cin >> userChoiceMenu;
            }
        }
        else if (intChoice == 6) {
            //get Crime counts
            cout << "All crime counts by Area:" << endl;
            PrintMostOrLeast(areaCount, areaIDMap, true, areaCount.size());
            cout << "Press any key and enter to return to menu." << endl;
            cin >> userChoiceMenu;
        }
        else if (intChoice == 7) {
            // Test and Verify Merge vs Heap Sort
            cout << "Area Data:" <<endl;
            cout << "Validating sort methods..." << endl;
            VerifyAndReportSort(heapAreas,mergeAreas, heapAreaT, mergeAreaT);
            cout << endl << "Crime Data:" <<endl;
            cout << "Validating sort methods..." << endl;
            VerifyAndReportSort(heapCrime, mergeCrime, heapCrimeT, mergeCrimeT);
            cout << "Press any key and enter to return to menu." << endl;
            cin >> userChoiceMenu;
        }
        else if (intChoice == 8) {
            cout << "Exiting application. Have a good one!" << endl;
            exit = true;
        }
        //reset input validation
        choiceMenuValid = false;
        choiceCountValid = false;
    }
    while (!exit);
    return 0;
}