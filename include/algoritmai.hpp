#pragma once

#include <functional>
#include <type_traits>
#include <vector>

#include "helper.hpp"

namespace sd3 {

template <bool kCountStats = false, typename T, typename TCompare = std::less<>>
  requires(std::is_invocable_r<bool, TCompare, const T&, const T&>::value)
void heapsort(std::vector<T>& data, TCompare&& compare, SortStats* stats = nullptr) { }

// TODO: Nereikia sito kaip suprantu
// void quicksort_middle(std::vector<int>& data);
// void quicksort_median(std::vector<int>& data);
// void shellsort_sedgewick(std::vector<int>& data);
// void shellsort_ciura(std::vector<int>& data);
// void mergesort(std::vector<int>& data);
// void timsort(std::vector<int>& data);

};
