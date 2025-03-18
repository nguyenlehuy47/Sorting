#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "algorithms/sortingAlgorithms.h"
#include "utils/timer.h"
#include "utils/file_io.h"
#include "DataGenerator/DataGenerator.h"
#include "utils/xlsxwriter.h" // Include the xlsxwriter header

using namespace std;

// Hàm kiểm tra xem một chuỗi có phải là số nguyên hay không
bool isNumber(const string& str) {
    for (char ch : str) {
        if (!isdigit(ch)) {
            return false;
        }
    }
    return true;
}

// Hàm chạy thuật toán và in kết quả
void runAlgorithm(const string& algorithm, vector<int>& data, const string& outputParam, long long& comparisons, long long& runtime) {
    auto start = startTimer();
    comparisons = 0;

    cout << "Running " << algorithm << "..." << endl; // Debug statement

    if (algorithm == "selection-sort") {
        selectionSort(data, comparisons);
    } else if (algorithm == "insertion-sort") {
        insertionSort(data, comparisons);
    } else if (algorithm == "binary-insertion-sort") {
        binaryInsertionSort(data, comparisons);
    } else if (algorithm == "bubble-sort") {
        bubbleSort(data, comparisons);
    } else if (algorithm == "shaker-sort") {
        shakerSort(data, comparisons);
    } else if (algorithm == "shell-sort") {
        shellSort(data, comparisons);
    } else if (algorithm == "heap-sort") {
        heapSort(data, comparisons);
    } else if (algorithm == "merge-sort") {
        mergeSort(data, comparisons);
    } else if (algorithm == "quick-sort") {
        quickSort(data, comparisons);
    } else if (algorithm == "counting-sort") {
        countingSort(data, comparisons);
    } else if (algorithm == "radix-sort") {
        radixSort(data, comparisons);
    } else if (algorithm == "flash-sort") {
        flashSort(data, comparisons);
    } else {
        cout << "Error: Unknown algorithm!" << endl;
        return;
    }

    runtime = endTimer(start);
    cout << algorithm << " completed." << endl; // Debug statement
}

// Hàm chạy tất cả các thuật toán và ghi kết quả vào file CSV
void runAllAlgorithms(const vector<int>& data, const string& outputParam) {
    vector<string> algorithms = {
        "selection-sort", "insertion-sort", "binary-insertion-sort", "bubble-sort",
        "shaker-sort", "shell-sort", "heap-sort", "merge-sort", "quick-sort",
        "counting-sort", "radix-sort", "flash-sort"
    };

    vector<long long> runtimes;
    vector<long long> comparisonsList;

    for (const string& algorithm : algorithms) {
        vector<int> dataCopy = data; // Sao chép dữ liệu để đảm bảo công bằng
        long long comparisons = 0, runtime = 0;
        cout << "Running algorithm: " << algorithm << endl; // Debug statement
        runAlgorithm(algorithm, dataCopy, outputParam, comparisons, runtime);
        runtimes.push_back(runtime);
        comparisonsList.push_back(comparisons);
    }

    // Write results to CSV file
    writeResultsToCSV("all_algorithms_results.csv", algorithms, runtimes, comparisonsList);
    cout << "Results written to CSV file." << endl; // Debug statement
}

// Hàm xử lý Command 1 và Command 2
void handleAlgorithmMode(const string& algorithm, const string& inputFile, const string& outputParam, int size = 0, const string& order = "") {
    vector<int> data;

    if (!inputFile.empty()) {
        // Command 1: Đọc dữ liệu từ file
        data = readDataFromFile(inputFile);
    } else {
        // Command 2: Tạo dữ liệu tự động
        int* arr = new int[size];
        if (order == "-rand") {
            GenerateRandomData(arr, size);
        } else if (order == "-nsorted") {
            GenerateNearlySortedData(arr, size);
        } else if (order == "-sorted") {
            GenerateSortedData(arr, size);
        } else if (order == "-rev") {
            GenerateReverseData(arr, size);
        } else {
            cout << "Error: Invalid input order!" << endl;
            delete[] arr;
            return;
        }
        data.assign(arr, arr + size);
        delete[] arr;
        writeDataToFile("input.txt", data); // Ghi dữ liệu vào file input.txt
    }

    long long comparisons = 0, runtime = 0;
    runAlgorithm(algorithm, data, outputParam, comparisons, runtime);

    // In kết quả
    cout << "ALGORITHM MODE" << endl;
    cout << "Algorithm: " << algorithm << endl;
    if (!inputFile.empty()) {
        cout << "Input file: " << inputFile << endl;
    } else {
        cout << "Input size: " << size << endl;
        cout << "Input order: " << order << endl;
    }
    cout << "Input size: " << data.size() << endl;
    if (outputParam == "-time" || outputParam == "-both") {
        cout << "Running time: " << runtime << " ms" << endl;
    }
    if (outputParam == "-comp" || outputParam == "-both") {
        cout << "Comparisons: " << comparisons << endl;
    }

    // Ghi kết quả vào file
    writeDataToFile("output.txt", data);

    // Write results to Excel file
    vector<string> algorithms = {algorithm};
    vector<long long> runtimes = {runtime};
    vector<long long> comparisonsList = {comparisons};
    

    // Write results to CSV file
    writeResultsToCSV("results.csv", algorithms, runtimes, comparisonsList);
}

// Hàm xử lý Command 3
void handleAlgorithmModeAllOrders(const string& algorithm, int size, const string& outputParam) {
    vector<string> orders = {"-rand", "-nsorted", "-sorted", "-rev"};

    for (const string& order : orders) {
        int* arr = new int[size];
        if (order == "-rand") {
            GenerateRandomData(arr, size);
        } else if (order == "-nsorted") {
            GenerateNearlySortedData(arr, size);
        } else if (order == "-sorted") {
            GenerateSortedData(arr, size);
        } else if (order == "-rev") {
            GenerateReverseData(arr, size);
        }
        vector<int> data(arr, arr + size);
        delete[] arr;

        string inputFile = "input_" + order.substr(1) + ".txt";
        writeDataToFile(inputFile, data); // Ghi dữ liệu vào file

        long long comparisons = 0, runtime = 0;
        runAlgorithm(algorithm, data, outputParam, comparisons, runtime);

        // In kết quả
        cout << "ALGORITHM MODE" << endl;
        cout << "Algorithm: " << algorithm << endl;
        cout << "Input size: " << size << endl;
        cout << "Input order: " << order << endl;
        if (outputParam == "-time" || outputParam == "-both") {
            cout << "Running time: " << runtime << " ms" << endl;
        }
        if (outputParam == "-comp" || outputParam == "-both") {
            cout << "Comparisons: " << comparisons << endl;
        }
        cout << "-------------------------" << endl;
    }
}

// Hàm xử lý Command 4 và Command 5
void handleComparisonMode(const string& algorithm1, const string& algorithm2, const string& inputFile, int size = 0, const string& order = "") {
    vector<int> data;

    if (!inputFile.empty()) {
        // Command 4: Đọc dữ liệu từ file
        data = readDataFromFile(inputFile);
    } else {
        // Command 5: Tạo dữ liệu tự động
        int* arr = new int[size];
        if (order == "-rand") {
            GenerateRandomData(arr, size);
        } else if (order == "-nsorted") {
            GenerateNearlySortedData(arr, size);
        } else if (order == "-sorted") {
            GenerateSortedData(arr, size);
        } else if (order == "-rev") {
            GenerateReverseData(arr, size);
        } else {
            cout << "Error: Invalid input order!" << endl;
            delete[] arr;
            return;
        }
        data.assign(arr, arr + size);
        delete[] arr;
        writeDataToFile("input.txt", data); // Ghi dữ liệu vào file input.txt
    }

    long long comparisons1 = 0, runtime1 = 0;
    long long comparisons2 = 0, runtime2 = 0;

    vector<int> data1 = data; // Sao chép dữ liệu để đảm bảo công bằng
    vector<int> data2 = data;

    runAlgorithm(algorithm1, data1, "-both", comparisons1, runtime1);
    runAlgorithm(algorithm2, data2, "-both", comparisons2, runtime2);

    // In kết quả
    cout << "COMPARE MODE" << endl;
    cout << "Algorithm: " << algorithm1 << " | " << algorithm2 << endl;
    if (!inputFile.empty()) {
        cout << "Input file: " << inputFile << endl;
    } else {
        cout << "Input size: " << size << endl;
        cout << "Input order: " << order << endl;
    }
    cout << "Input size: " << data.size() << endl;
    cout << "Running time: " << runtime1 << " ms | " << runtime2 << " ms" << endl;
    cout << "Comparisons: " << comparisons1 << " | " << comparisons2 << endl;

    // Write results to Excel file
    vector<string> algorithms = {algorithm1, algorithm2};
    vector<long long> runtimes = {runtime1, runtime2};
    vector<long long> comparisonsList = {comparisons1, comparisons2};
    
    // Write results to CSV file
    writeResultsToCSV("comparison_results.csv", algorithms, runtimes, comparisonsList);
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "Usage: " << argv[0] << " -a [Algorithm] [Input file] [Output parameter]" << endl;
        cout << "       " << argv[0] << " -a [Algorithm] [Input size] [Input order] [Output parameter]" << endl;
        cout << "       " << argv[0] << " -a [Algorithm] [Input size] [Output parameter]" << endl;
        cout << "       " << argv[0] << " -c [Algorithm 1] [Algorithm 2] [Input file]" << endl;
        cout << "       " << argv[0] << " -c [Algorithm 1] [Algorithm 2] [Input size] [Input order]" << endl;
        cout << "       " << argv[0] << " -all [Input file] [Output parameter]" << endl;
        cout << "       " << argv[0] << " -all [Input size] [Input order] [Output parameter]" << endl;
        return 1;
    }

    string mode = argv[1];

    if (mode == "-a") {
        string algorithm = argv[2];
        if (argc == 5) {
            string param3 = argv[3]; // Tham số thứ 3 (có thể là file hoặc số)
            string outputParam = argv[4];

            if (isNumber(param3)) {
                // Command 3: [Execution file] -a [Algorithm] [Input size] [Output parameter]
                int size = stoi(param3);
                handleAlgorithmModeAllOrders(algorithm, size, outputParam);
            } else {
                // Command 1: [Execution file] -a [Algorithm] [Input file] [Output parameter]
                string inputFile = param3;
                handleAlgorithmMode(algorithm, inputFile, outputParam);
            }
        } else if (argc == 6) {
            // Command 2: [Execution file] -a [Algorithm] [Input size] [Input order] [Output parameter]
            int size = stoi(argv[3]);
            string order = argv[4];
            string outputParam = argv[5];
            handleAlgorithmMode(algorithm, "", outputParam, size, order);
        } else {
            cout << "Error: Invalid number of arguments for Algorithm Mode!" << endl;
            return 1;
        }
    } else if (mode == "-c") {
        string algorithm1 = argv[2];
        string algorithm2 = argv[3];
        if (argc == 5) {
            // Command 4: [Execution file] -c [Algorithm 1] [Algorithm 2] [Input file]
            string inputFile = argv[4];
            handleComparisonMode(algorithm1, algorithm2, inputFile);
        } else if (argc == 6) {
            // Command 5: [Execution file] -c [Algorithm 1] [Algorithm 2] [Input size] [Input order]
            int size = stoi(argv[4]);
            string order = argv[5];
            handleComparisonMode(algorithm1, algorithm2, "", size, order);
        } else {
            cout << "Error: Invalid number of arguments for Comparison Mode!" << endl;
            return 1;
        }
    } else if (mode == "-all") {
        if (argc == 4) {
            // Command: [Execution file] -all [Input file] [Output parameter]
            string inputFile = argv[2];
            string outputParam = argv[3];
            vector<int> data = readDataFromFile(inputFile);
            runAllAlgorithms(data, outputParam);
        } else if (argc == 5) {
            // Command: [Execution file] -all [Input size] [Input order] [Output parameter]
            int size = stoi(argv[2]);
            string order = argv[3];
            string outputParam = argv[4];
            cout << "Generating data..." << endl; // Debug statement
            int* arr = new int[size];
            if (order == "-rand") {
                GenerateRandomData(arr, size);
            } else if (order == "-nsorted") {
                GenerateNearlySortedData(arr, size);
            } else if (order == "-sorted") {
                GenerateSortedData(arr, size);
            } else if (order == "-rev") {
                GenerateReverseData(arr, size);
            } else {
                cout << "Error: Invalid input order!" << endl;
                delete[] arr;
                return 1;
            }
            cout << "Data generated successfully." << endl; // Debug statement
            vector<int> data(arr, arr + size);
            delete[] arr;
            cout << "Running all algorithms..." << endl; // Debug statement
            runAllAlgorithms(data, outputParam);
            cout << "All algorithms executed successfully." << endl; // Debug statement
        } else {
            cout << "Error: Invalid number of arguments for All Algorithms Mode!" << endl;
            return 1;
        }
    } else {
        cout << "Error: Invalid mode!" << endl;
        return 1;
    }

    return 0;
}