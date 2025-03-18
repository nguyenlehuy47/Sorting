#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Khai báo các hàm sắp xếp với tham số comparisonCount (kiểu long long)
void selectionSort(vector<int>& arr, long long& comparisonCount);
void insertionSort(vector<int>& arr, long long& comparisonCount);
void binaryInsertionSort(vector<int>& arr, long long& comparisonCount);
void bubbleSort(vector<int>& arr, long long& comparisonCount);
void shakerSort(vector<int>& arr, long long& comparisonCount);
void shellSort(vector<int>& arr, long long& comparisonCount);
void heapSort(vector<int>& arr, long long& comparisonCount);
void mergeSort(vector<int>& arr, long long& comparisonCount);
void quickSort(vector<int>& arr, long long& comparisonCount);
void countingSort(vector<int>& arr, long long& comparisonCount);
void radixSort(vector<int>& arr, long long& comparisonCount);
void flashSort(vector<int>& arr, long long& comparisonCount);

#endif