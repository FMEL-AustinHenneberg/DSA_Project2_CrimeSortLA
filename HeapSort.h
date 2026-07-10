//
// Created by Miguel Gutierrez on 7/9/26.
//
#ifndef DSA_PROJECT2_CRIMESORTLA_HEAPSORT_H
#define DSA_PROJECT2_CRIMESORTLA_HEAPSORT_H

#include <vector>
#include <utility>
#include <unordered_map>
#inlcude "Crime.h"
using namespace std;

void heapifyDown(vector<pair<int,int>>& arr, int heapSize, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heapSize && arr[left].second > arr[largest].second) {
        largest = left;
    }
    if (right < heapSize && arr[right].second > arr[largest].second) {
        largest = right;
    }
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapifyDown(arr, heapSize, largest);
    }
}

void heapSort(vector<pair<int,int>>& arr) {
    int n = arr.size();

    for (int i = n/2 - 1; i >= 0; i--) {
        heapifyDown(arr, n, i);
    }
    for (int i = n -1; i >= 1; i--) {
        swap(arr[0], arr[i]);
        heapifyDown(arr, i, 0);
    }
}

vector<pair<int,int>> countByCrime(const vector<Crime::Record>& records) {
    unordered_map<int,int> counts;

    for (const auto& r : records) {
        counts[r.crimeID]++;
    }

    vector<pair<int,int>> result;
    for (const auto& p : counts) {
        result.push_back(p);
    }
    return result;
}

vector<pair<int,int>> countByArea(const vector<Crime::Record>& records) {
    unordered_map<int,int> counts;

    for (const auto& r : records) {
        counts[r.areaID]++;
    }

    vector<pair<int,int>> result;
    for (const auto& p : counts) {
        result.push_back(p);
    }
    return result;
}

#endif //DSA_PROJECT2_CRIMESORTLA_HEAPSORT_H


