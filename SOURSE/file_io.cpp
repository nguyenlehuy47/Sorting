#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "utils/file_io.h"
#include "DataGenerator/DataGenerator.h"

using namespace std;

// Hàm đọc dữ liệu từ file
vector<int> readDataFromFile(const string& filename) {
    ifstream file(filename);
    vector<int> data;
    int n, value;

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return data;
    }

    file >> n; // Đọc số lượng phần tử
    for (int i = 0; i < n; i++) {
        file >> value; // Đọc từng phần tử
        data.push_back(value);
    }

    file.close();
    return data;
}

// Hàm ghi dữ liệu vào file
void writeDataToFile(const string& filename, const vector<int>& data) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    file << data.size() << endl; // Ghi số lượng phần tử
    for (int value : data) {
        file << value << " "; // Ghi từng phần tử
    }

    file.close();
}

// Hàm sinh dữ liệu và ghi vào file
void generateDataToFile(const string& filename, int n, int dataType) {
    vector<int> data(n);
    GenerateData(data.data(), n, dataType); // Sử dụng hàm từ DataGenerator.cpp
    writeDataToFile(filename, data);
}