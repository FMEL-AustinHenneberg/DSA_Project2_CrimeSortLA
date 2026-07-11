//
// Created by Angie Carten on 7/10/2026.
//

#ifndef DSA_PROJECT2_CRIMESORTLA_MERGESORT_H
#define DSA_PROJECT2_CRIMESORTLA_MERGESORT_H

#include <vector>
#include <map>
#include <string>
#include <utility>
using namespace std;

typedef pair<int, int> CrimeCount;

// Gets the crime name
string getCrimeName(int crimeID, const map<int, string>& crimeIDMap) {
    auto it = crimeIDMap.find(crimeID);

    if (it != crimeIDMap.end()) {
        return it->second;
    }
    return "";
}

bool comesBefore(const CrimeCount& left, const CrimeCount& right,
                 const map<int, string>& crimeIDMap, bool descending) {
    if (left.second != right.second) {
        if (descending) {
            return left.second > right.second; // most frequent first
        }
        else {
            return left.second < right.second; // least frequent first
        }
    }

    // If the counts are tied, sort alphabetically by crime name
    return getCrimeName(left.first, crimeIDMap) < getCrimeName(right.first, crimeIDMap);
}

// Combines two sorted halves
void merge(vector<CrimeCount>& crimes, int left, int middle, int right,
           const map<int, string>& crimeIDMap, bool descending) {
    vector<CrimeCount> temp;

    int i = left;
    int j = middle + 1;

    while (i <= middle && j <= right) {
        if (comesBefore(crimes[i], crimes[j], crimeIDMap, descending)) {
            temp.push_back(crimes[i]);
            i++;
        }
        else {
            temp.push_back(crimes[j]);
            j++;
        }
    }

    while (i <= middle) {
        temp.push_back(crimes[i]);
        i++;
    }

    while (j <= right) {
        temp.push_back(crimes[j]);
        j++;
    }

    for (int k = 0; k < temp.size(); k++) {
        crimes[left + k] = temp[k];
    }
}

// Recursive merge sort function
void mergeSortHelper(vector<CrimeCount>& crimes, int left, int right,
                     const map<int, string>& crimeIDMap, bool descending) {
    if (left >= right) {
        return;
    }

    int middle = left + (right - left) / 2;

    mergeSortHelper(crimes, left, middle, crimeIDMap, descending);
    mergeSortHelper(crimes, middle + 1, right, crimeIDMap, descending);
    merge(crimes, left, middle, right, crimeIDMap, descending);
}

void mergeSort(vector<CrimeCount>& crimes, const map<int, string>& crimeIDMap, bool descending) {
    if (!crimes.empty()) {
        mergeSortHelper(crimes, 0, crimes.size() - 1, crimeIDMap, descending);
    }
}
#endif //DSA_PROJECT2_CRIMESORTLA_MERGESORT_H