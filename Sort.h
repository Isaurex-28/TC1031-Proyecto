#ifndef SORT_H
#define SORT_H

#include <vector>
#include "Corral.h"

using namespace std;


bool compareCorrals(const Corral& a, const Corral& b, int comparison) {
    switch (comparison) {
        case 1:
            return a.getTotalPlortValue() >= b.getTotalPlortValue();
        case 2:
            return a.getTotalFoodNeeded() >= b.getTotalFoodNeeded();
        case 3:
        default:
            return a.getQuantity() >= b.getQuantity();
    }
}

void copyArray(vector<Corral>& A, vector<Corral>& B, int low, int high) {
    for (int i = low; i <= high; i++) {
        A[i] = B[i];
    }
}

void mergeArray(vector<Corral>& A, vector<Corral>& B, int low, int mid, int high, int comparison) {
    int i = low;
    int j = mid + 1;
    int k = low;

    while (i <= mid && j <= high) {
        if (compareCorrals(A[i], A[j], comparison)) {
            B[k++] = A[i++];
        } else {
            B[k++] = A[j++];
        }
    }
    while (i <= mid) B[k++] = A[i++];
    while (j <= high) B[k++] = A[j++];
}

void mergeSplit(vector<Corral>& A, vector<Corral>& B, int low, int high, int comparison) {
    if (high - low < 1) return;
    int mid = (high + low) / 2;
    mergeSplit(A, B, low, mid, comparison);
    mergeSplit(A, B, mid + 1, high, comparison);
    mergeArray(A, B, low, mid, high, comparison);
    copyArray(A, B, low, high);
}

vector<Corral> mergeSort(const vector<Corral>& source, int comparison) {
    vector<Corral> v(source);
    if (v.empty()) return v;
    vector<Corral> tmp(v.size());
    mergeSplit(v, tmp, 0, static_cast<int>(v.size()) - 1, comparison);
    return v;
}

#endif