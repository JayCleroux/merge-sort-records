#include "MergeSort.h"
// Construct the MergeSort with a file path and field to sort
MergeSort::MergeSort(std::string file_path, int sort_col) : m_file_path(
std::move(file_path)), m_field(sort_col) {}

bool MergeSort::sort_file() {

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
    // Split each line into fields and sort the vector of lines
    std::vector<std::string> data;
    for (auto &line: lines) {
        std::vector<std::string> fields = split(line, '\t');
        // Add the specified sort column from the line
        if (m_field < fields.size()) {
            data.push_back(line);
        }
    }

    merge_sort(data, 0, data.size() - 1);
    // Write the sorted lines back to the file
    std::ofstream out_file(m_file_path);
    for (auto &line: data) {
        out_file << line << std::endl;
    }
    out_file.close();

    return true;
}
// Returns a vector of strings representing the individual fields.
std::vector<std::string> MergeSort::split(const std::string &str, char delim) {

    std::vector<std::string> fields;
    // Create a stringstream object from the input string
    std::stringstream ss(str);
    std::string field;
    // Loop through each field in the stringstream, extracting it based on the
    // delimiter and adding it to the vector of fields
    while (getline(ss, field, delim)) {
        fields.push_back(field);
    }

    return fields;
}
// This method implements the merge sort algorithm to sort a vector of strings
void MergeSort::merge_sort(std::vector<std::string> &data, int left, int right) {

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
        // Compare the elements at i and j using the compare method
        // If the element at i is smaller or equal, add it to the temp array
        if (compare(data[i], data[j])) {
            temp[k++] = data[i++];
        }
        // Otherwise, add the element at j to the temp array
        else {
            temp[k++] = data[j++];
        }
    }
    // Copy the  elements from the left subarray to the temporary vector
    while (i <= mid) temp[k++] = data[i++];
    // Copy the elements from the right subarray to the temporary vector
    while (j <= right) temp[k++] = data[j++];
    // Copy the sorted elements from the temporary vector back to the original
    for (int p = 0; p < k; p++) {
        data[left + p] = temp[p];
    }
}

bool MergeSort::compare(const std::string &str1, const std::string &str2) const {
    // Split the strings by the tab delimiter
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

    if (is_integer(val1) && is_integer(val2)) {
        return stoi(val1) <= stoi(val2);
    }

    else {
        return val1 <= val2;
    }
}

bool MergeSort::is_integer(const std::string &str) {

    for (char c: str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

