#include "xlsxwriter.h"
#include <fstream>
#include <vector>
#include <string>   
#include <iostream>

#define ROW_COUNT_FILE "output/row_count.txt"

/// Đọc số hàng đã ghi từ file `row_count.txt`
int getStartingRow() {
    std::ifstream infile(ROW_COUNT_FILE);
    int row = 1; // Mặc định là 1 (bỏ qua tiêu đề)
    if (infile) {
        infile >> row;
    }
    infile.close();
    return row;
}

/// Lưu số hàng mới vào file `row_count.txt`
void saveNewRowCount(int newRow) {
    std::ofstream outfile(ROW_COUNT_FILE, std::ios::trunc);
    outfile << newRow;
    outfile.close();
}

/// Ghi dữ liệu vào Excel mà không ghi đè dữ liệu cũ
void writeResultsToExcel(const std::string& filename, 
                         const std::vector<std::string>& algorithms, 
                         const std::vector<long long>& runtimes, 
                         const std::vector<long long>& comparisons) {
    lxw_workbook  *workbook  = workbook_new(filename.c_str());
    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, "Results");

    int startRow = getStartingRow();

    // Nếu đây là lần đầu tiên ghi, thêm tiêu đề

    // Ghi dữ liệu tiếp theo từ dòng `startRow`
    for (size_t i = 0; i < algorithms.size(); ++i) {
        worksheet_write_string(worksheet, startRow + i, 0, algorithms[i].c_str(), NULL);
        worksheet_write_number(worksheet, startRow + i, 1, runtimes[i], NULL);
        worksheet_write_number(worksheet, startRow + i, 2, comparisons[i], NULL);
    }

    workbook_close(workbook);
    
    // Lưu số hàng mới vào file
    saveNewRowCount(startRow + algorithms.size());
}

/// Ghi dữ liệu vào CSV mà không ghi đè dữ liệu cũ
void writeResultsToCSV(const std::string& filename, 
                       const std::vector<std::string>& algorithms, 
                       const std::vector<long long>& runtimes, 
                       const std::vector<long long>& comparisons) {
    std::ofstream outfile(filename, std::ios::app);
    if (!outfile) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    int startRow = getStartingRow();

    // Nếu đây là lần đầu tiên ghi, thêm tiêu đề

    // Ghi dữ liệu tiếp theo từ dòng `startRow`
    for (size_t i = 0; i < algorithms.size(); ++i) {
        outfile << algorithms[i] << "," << runtimes[i] << "," << comparisons[i] << "\n";
    }

    saveNewRowCount(startRow + algorithms.size());
    outfile.close();
}
