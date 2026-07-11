//
// Created by Angie Carten on 7/10/2026.
//

#ifndef DSA_PROJECT2_CRIMESORTLA_MERGESORT_H
#define DSA_PROJECT2_CRIMESORTLA_MERGESORT_H

#include <vector>
#include <utility>
using namespace std;

// Combines two sorted halves
void merge(vector<pair<int, int>>& data, int left, int middle, int right) {
    vector<pair<int, int>> temp;

    int i = left;
    int j = middle + 1;

    while (i <= middle && j <= right) {
        // Sort by the second value, matching Heap Sort
        if (data[i].second <= data[j].second) {
            temp.push_back(data[i]);
            i++;
        }
        else {
            temp.push_back(data[j]);
            j++;
        }
    }

    // Copy any remaining values from the left half
    while (i <= middle) {
        temp.push_back(data[i]);
        i++;
    }

    // Copy any remaining values from the right half
    while (j <= right) {
        temp.push_back(data[j]);
        j++;
    }

    // Copy the sorted values back into the original vector
    for (int k = 0; k < temp.size(); k++) {
        data[left + k] = temp[k];
    }
}

// Divides the vector into smaller sections
void mergeSortHelper(vector<pair<int, int>>& data, int left, int right) {
    if (left >= right) {
        return;
    }

    int middle = left + (right - left) / 2;

    mergeSortHelper(data, left, middle);
    mergeSortHelper(data, middle + 1, right);

    merge(data, left, middle, right);
}

// Function called from main.cpp
void mergeSort(vector<pair<int, int>>& data) {
    if (!data.empty()) {
        mergeSortHelper(data, 0, data.size() - 1);
    }
}

#endif //DSA_PROJECT2_CRIMESORTLA_MERGESORT_H