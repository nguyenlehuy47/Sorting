#include <iostream>
#include <vector>
#include <algorithm>
#include "algorithms/sortingAlgorithms.h"
using namespace std;

// Selection Sort
void selectionSort(vector<int>& arr, long long& comparisonCount) {
    int n = arr.size();
    comparisonCount = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            comparisonCount++;
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

// Insertion Sort
void insertionSort(vector<int>& arr, long long& comparisonCount) {
    int n = arr.size();
    comparisonCount = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            comparisonCount++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }
}

// Binary Insertion Sort
void binaryInsertionSort(vector<int>& arr, long long& comparisonCount) {
    int n = arr.size();
    comparisonCount = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int left = 0, right = i - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            comparisonCount++;
            if (arr[mid] > key) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        for (int j = i - 1; j >= left; j--) {
            arr[j + 1] = arr[j];
        }
        arr[left] = key;
    }
}

// Bubble Sort
void bubbleSort(vector<int>& arr, long long& comparisonCount) {
    int n = arr.size();
    comparisonCount = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisonCount++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Shaker Sort
void shakerSort(vector<int>& arr, long long& comparisonCount) {
    int n = arr.size();
    comparisonCount = 0;
    int left = 0, right = n - 1;
    while (left < right) {
        for (int i = left; i < right; i++) {
            comparisonCount++;
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
            }
        }
        right--;
        for (int i = right; i > left; i--) {
            comparisonCount++;
            if (arr[i - 1] > arr[i]) {
                swap(arr[i - 1], arr[i]);
            }
        }
        left++;
    }
}

// Shell Sort
void shellSort(vector<int>& arr, long long& comparisonCount) {
    int n = arr.size();
    comparisonCount = 0;
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap; j -= gap) {
                comparisonCount++;
                if (arr[j - gap] > temp) {
                    arr[j] = arr[j - gap];
                } else {
                    break;
                }
            }
            arr[j] = temp;
        }
    }
}

// Heap Sort
void heapify(vector<int>& arr, int n, int i, long long& comparisonCount) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
        comparisonCount++;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
        comparisonCount++;
    }
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest, comparisonCount);
    }
}

void heapSort(vector<int>& arr, long long& comparisonCount) {
    int n = arr.size();
    comparisonCount = 0;

    // Xây dựng max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, comparisonCount);
    }

    // Trích xuất từng phần tử từ heap
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0, comparisonCount);
    }
}

// Merge Sort
void merge(vector<int>& arr, int left, int mid, int right, long long& comparisonCount) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        comparisonCount++;
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int left, int right, long long& comparisonCount) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, comparisonCount);
        mergeSort(arr, mid + 1, right, comparisonCount);
        merge(arr, left, mid, right, comparisonCount);
    }
}

void mergeSort(vector<int>& arr, long long& comparisonCount) {
    comparisonCount = 0;
    mergeSort(arr, 0, arr.size() - 1, comparisonCount);
}

// Quick Sort
int partition(vector<int>& arr, int low, int high, long long& comparisonCount) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        comparisonCount++;
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high, long long& comparisonCount) {
    if (low < high) {
        int pi = partition(arr, low, high, comparisonCount);
        quickSort(arr, low, pi - 1, comparisonCount);
        quickSort(arr, pi + 1, high, comparisonCount);
    }
}

void quickSort(vector<int>& arr, long long& comparisonCount) {
    comparisonCount = 0;
    quickSort(arr, 0, arr.size() - 1, comparisonCount);
}

// Counting Sort
void countingSort(vector<int>& arr, long long& comparisonCount) {
    int maxVal = *max_element(arr.begin(), arr.end());
    vector<int> count(maxVal + 1, 0);
    comparisonCount = 0;

    for (int num : arr) {
        count[num]++;
        comparisonCount++;
    }

    int index = 0;
    for (int i = 0; i <= maxVal; i++) {
        while (count[i]-- > 0) {
            arr[index++] = i;
        }
    }
}

// Radix Sort
void radixSort(vector<int>& arr, long long& comparisonCount) {
    int maxVal = *max_element(arr.begin(), arr.end());
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        vector<int> output(arr.size());
        vector<int> count(10, 0);
        for (int num : arr) {
            count[(num / exp) % 10]++;
            comparisonCount++;
        }
        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];
        for (int i = arr.size() - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }
        arr = output;
    }
}

void flashSort(vector<int>& arr, long long& comparisonCount) {
    int n = arr.size();
    int minVal = *min_element(arr.begin(), arr.end());
    int maxIdx = max_element(arr.begin(), arr.end()) - arr.begin();
    comparisonCount = 0;

    if (minVal == arr[maxIdx]) return;

    int m = max(1, int(0.45 * n));  // Đảm bảo m >= 1
    vector<int> L(m, 0);

    for (int i = 0; i < n; i++) {
        int k = min(m - 1, (m * (arr[i] - minVal)) / (arr[maxIdx] - minVal));
        L[k]++;
        comparisonCount++;
    }

    for (int i = 1; i < m; i++)
        L[i] += L[i - 1];

    int count = 0, index = 0;
    while (count < n) {
        int k = min(m - 1, (m * (arr[index] - minVal)) / (arr[maxIdx] - minVal));
        while (index < n && index >= L[k]) {
            index++;
            if (index >= n) return;
            k = min(m - 1, (m * (arr[index] - minVal)) / (arr[maxIdx] - minVal));
        }

        int value = arr[index];
        while (index != L[k]) {
            k = min(m - 1, (m * (value - minVal)) / (arr[maxIdx] - minVal));
            if (L[k] > 0) {
                swap(value, arr[--L[k]]);
            }
            count++;
            comparisonCount++;
        }
    }
}
