#pragma once

#include <cassert>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <ranges>
#include <span>
#include <type_traits>
#include <vector>

namespace sd3 {

struct SortStats {
  uint64_t swaps = 0;
  uint64_t comparisons = 0;
};

void heapsort(std::vector<unsigned int>& data, SortStats& stats);

// INFO: Nereikia šitų kaip suprantu
// void quicksort_middle(std::vector<unsigned int>& data);
// void quicksort_median(std::vector<unsigned int>& data);
// void shellsort_sedgewick(std::vector<unsigned int>& data);
// void shellsort_ciura(std::vector<unsigned int>& data);
// void mergesort(std::vector<unsigned int>& data);
// void timsort(std::vector<unsigned int>& data);

};
