#pragma once

#include <vector>

namespace sd3 {

void heapsort(std::vector<int>& data);
void quicksort_middle(std::vector<int>& data);
void quicksort_median(std::vector<int>& data);
void shellsort_sedgewick(std::vector<int>& data);
void shellsort_ciura(std::vector<int>& data);
void mergesort(std::vector<int>& data);
void timsort(std::vector<int>& data);

};
