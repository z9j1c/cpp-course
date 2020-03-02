#include "stat_int.h"
#include <iostream>
#include <utility>

void bubble_sort(StatisticsInt* buff, int len) {
    for (int i = 0; i < len; ++i) {
        bool swaps_flag = false;
        
        for (int j = 0; j < len - 1; ++j) {
            if (buff[j] > buff[j + 1]) {
                std::swap(buff[j], buff[j + 1]);
                swaps_flag = true;
            }
        }

        if (!swaps_flag) {
            break;
        }
    }
}

int main() {
    int elem_count;
    std::cout << "Enter elements count: ";
    std::cin >> elem_count;

    StatisticsInt input[elem_count];
    for (int i = 0; i < elem_count; ++i) {
        input[i] = elem_count - i;
    }

    std::cout << "Unsorted: ";
    for (int i = 0; i < elem_count; ++i) {
        std::cout << input[i] << " ";
    }

    bubble_sort(input, elem_count);
    
    std::cout << "\nSorted:   ";
    for (int i = 0; i < elem_count; ++i) {
        std::cout << input[i] << " ";
    }
    
    std::cout << "\n\nTotal operations count: " << StatisticsInt::GetGlobalOpsCount() <<
                 "\nTotal comparisons count: " << StatisticsInt::GetGlobalCompCount() <<
                 "\nTotal assignings count: " << StatisticsInt::GetGlobalAssignCount() <<
                 "\nTotal arithmetic operations count: " << StatisticsInt::GetGlobalArithmCount() <<
                 "\nTotal binary operations count: " << StatisticsInt::GetGlobalBinCount();

    return 0;
}