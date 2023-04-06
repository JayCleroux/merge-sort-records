#include "MergeSort.h"

int main(int argc, char *argv[]) {

    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <filename> -field=<fieldno>"
                  << std::endl;
        return 0;
    }

    std::string file_name = argv[1];
    std::string str = argv[2];

    if (str.substr(0, 7) != "-field=") {
        std::cerr << "Usage: " << argv[0] << " <filename> -field=<fieldno>"
                  << std::endl;
        return 1;
    }

    std::string row_str = str.substr(7);
    int field_no = 0;

    try {
        field_no = stoi(row_str);
    } catch (const std::invalid_argument &e) {
        std::cerr << "Usage: " << argv[0] << " <filename> -field=<fieldno>"
                  << std::endl;
        return 1;
    }

    MergeSort ms(file_name, field_no);
    ms.sort_file();
    return 0;
}







