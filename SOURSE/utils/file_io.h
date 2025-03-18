#ifndef FILE_IO_H
#define FILE_IO_H

using namespace std;


vector<int> readDataFromFile(const string& filename);

void writeDataToFile(const string& filename, const vector<int>& data);

void generateDataToFile(const string& filename, int n, int dataType);

#endif
