#ifndef SORT_H
#define SORT_H

#include "Slime.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>


using namespace std;
 
void copyArray(vector<Slime>& A, vector<Slime>& B, int low, int high) {
    for (int i = low; i <= high; i++) {
        A[i] = B[i];
    }
}
 
void mergeArray(vector<Slime>& A, vector<Slime>& B, int low, int mid, int high) {
    int i, j, k;
 
    i = low;
    j = mid + 1;
    k = low;
 
    while (i <= mid && j <= high) {
        if (A[i].getPlortVal() < A[j].getPlortVal()) {
            B[k] = A[i];
            i++;
        } else {
            B[k] = A[j];
            j++;
        }
        k++;
    }
    if (i > mid) {
        for (; j <= high; j++) {
            B[k++] = A[j];
        }
    } else {
        for (; i <= mid; i++) {
            B[k++] = A[i];
        }
    }
}
 
void mergeSplit(vector<Slime>& A, vector<Slime>& B, int low, int high) {
    int mid;
 
    if ((high - low) < 1) {
        return;
    }
    mid = (high + low) / 2;
    mergeSplit(A, B, low, mid);
    mergeSplit(A, B, mid + 1, high);
    mergeArray(A, B, low, mid, high);
    copyArray(A, B, low, high);
}
 

vector<Slime> mergeSort(const vector<Slime>& source) {
    vector<Slime> v(source);
    vector<Slime> tmp(v.size());
  
    mergeSplit(v, tmp, 0, (int)v.size() - 1);
    return v;
}

#endif