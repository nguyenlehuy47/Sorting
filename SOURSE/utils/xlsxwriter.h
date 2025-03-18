#ifndef XLSXWRITER_H
#define XLSXWRITER_H

#include <string>
#include <vector>

void writeResultsToCSV(const std::string& filename, const std::vector<std::string>& algorithms, const std::vector<long long>& runtimes, const std::vector<long long>& comparisons);

#endif // XLSXWRITER_H