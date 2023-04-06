#include "MergeSort.h"

MergeSort::MergeSort(std::string file_path, int sort_col) : m_file_path(
std::move(file_path)), m_field(sort_col) {}

bool MergeSort::sort_file() {
    // Open input file
    std::ifstream file(m_file_path);
    if (!file) {
        std::cerr << "Error: cannot open file" << std::endl;
        return false;
    }

    // Read all lines of the file into a vector
    std::vector<std::string> lines;
    std::string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }

    // Split each line into fields and sort the vector of lines based on a specified field
    std::vector<std::string> data;
    for (auto &line: lines) {
        std::vector<std::string> fields = split(line, '\t');
        // Check that the specified sort column exists in the line
        if (m_field < fields.size()) {
            data.push_back(line);
        }
    }

    merge_sort(data, 0, data.size() - 1);
    // Write the sorted lines to a temporary file
    std::ofstream out_file(m_file_path);
    for (auto &line: data) {
        out_file << line << std::endl;
    }
    out_file.close();

    return true;
}
// Returns a vector of strings representing the individual fields.
std::vector<std::string> MergeSort::split(const std::string &str, char delim) {
    // Create an empty vector to store the individual fields.
    std::vector<std::string> fields;
    // Create a stringstream object from the input string.
    std::stringstream ss(str);
    // Declare a string variable to hold each field as it is extracted from the stringstream.
    std::string field;
    // Loop through each field in the stringstream, extracting it based on the delimiter
    // character and adding it to the vector of fields.
    while (getline(ss, field, delim)) {
        fields.push_back(field);
    }
    // Return the vector of fields.
    return fields;
}

// This method implements the merge sort algorithm to sort a vector of strings
void MergeSort::merge_sort(std::vector<std::string> &data, int left, int right) {
    // If the subarray has 0 or 1 elements, it is already sorted
    if (left >= right) return;
    // Divide the subarray into two parts
    int mid = (left + right) / 2;
    // Recursively sort the left and right subarrays
    merge_sort(data, left, mid);
    merge_sort(data, mid + 1, right);
    // Create a temporary vector to hold the merged subarrays
    std::vector<std::string> temp(right - left + 1);
    // Merge the two sorted subarrays into the temporary vector
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
        if (compare(data[i], data[j])) {
            temp[k++] = data[i++];
        } else {
            temp[k++] = data[j++];
        }
    }
    // Copy the remaining elements from the left subarray to the temporary vector
    while (i <= mid) temp[k++] = data[i++];
    // Copy the remaining elements from the right subarray to the temporary vector
    while (j <= right) temp[k++] = data[j++];
    // Copy the sorted elements from the temporary vector back to the original vector
    for (int p = 0; p < k; p++) {
        data[left + p] = temp[p];
    }
}

bool MergeSort::compare(const std::string &str1, const std::string &str2) const {
    // Split the strings by the specified delimiter
    std::vector<std::string> fields1 = split(str1, '\t');
    std::vector<std::string> fields2 = split(str2, '\t');
    // Check if the specified field index is valid for both strings
    if (m_field >= fields1.size() || m_field >= fields2.size()) {
        // If not, compare the entire strings and return the result
        return str1 <= str2;
    }

    // Get the values of the specified field for both strings
    std::string val1 = fields1[m_field];
    std::string val2 = fields2[m_field];
    // If the values are integers, compare them numerically
    if (is_integer(val1) && is_integer(val2)) {
        return stoi(val1) <= stoi(val2);
    }
        // If the values are floating-point numbers, compare them numerically
    else if (is_float(val1) && is_float(val2)) {
        return stof(val1) <= stof(val2);
    }
        // If the values are not numeric, compare them lexicographically
    else {
        return val1 <= val2;
    }
}

bool MergeSort::is_integer(const std::string &str) {
    if (str.empty()) return false;
    for (char c: str) {  // Iterate over each character in the string
        if (!isdigit(c)) return false;
    }
    return true;  // If all characters are digits, return true
}

bool MergeSort::is_float(const std::string &str) {
    if (str.empty()) return false;
    bool dot_found = false;
    for (char c: str) {
        if (!isdigit(c)) {
            if (c == '.' && !dot_found) {
                dot_found = true;
            } else {
                return false;
            }
        }
    }
    return dot_found;
}


