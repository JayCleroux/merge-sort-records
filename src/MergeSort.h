#ifndef ASSIGNMENT4_MERGESORT_H
#define ASSIGNMENT4_MERGESORT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <algorithm>
#include <string>

class MergeSort {
public:
    MergeSort(std::string file_path, int sort_col);

    bool sort_file();

private:
    std::string m_file_path;
    int m_field;

    static std::vector<std::string> split(const std::string &str, char delim);

    void merge_sort(std::vector<std::string> &data, int left, int right);

    bool compare(const std::string &str1, const std::string &str2) const;

    static bool is_integer(const std::string &str);

};

#endif //ASSIGNMENT4_MERGESORT_H