#pragma once

#include <cassert>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <ranges>
#include <span>
#include <type_traits>

namespace sd3 {

struct SortStats {
  uint64_t swaps = 0;
  uint64_t comparisons = 0;
};

/**
 * @brief Sorts a sequence using the Heapsort algorithm.
 *
 * @tparam kCountStats Whether to collect sorting statistics.
 * @tparam T Element type.
 * @tparam TCompare Comparator type used to determine element ordering.
 *
 * @param data Mutable span containing the elements to sort.
 * @param comp Comparator instance. Defaults to std::less<>.
 * @param stats Optional pointer to statistics storage.
 *
 * @note Complexity: O(n log n) time and O(1) auxiliary space.
 *
 * @warning The algorithm is not stable.
 */

// clang-format off
template <
  bool kCountStats = false,
  std::ranges::contiguous_range R,
  typename TCompare = std::less<>
>
requires 
  std::ranges::sized_range<R> &&
  (!std::is_const_v<
    std::remove_reference_t<
      std::ranges::range_reference_t<R>
    >
  >) &&
  std::strict_weak_order<
    TCompare&, 
    const std::ranges::range_value_t<R>&,
    const std::ranges::range_value_t<R>&
  > &&
  std::swappable<std::ranges::range_value_t<R>
>

// clang-format on
void heapsort(R&& range, TCompare comp = {}, SortStats* stats = nullptr) {
  // Baisiai perdarytas Heapsort algoritmas ;P

  using T = std::ranges::range_value_t<R>;

  std::span<T> data{std::ranges::data(range), std::ranges::size(range)};

  if (data.size() < 2) {
    return;
  }

  auto compare = [&](const T& l, const T& r) -> bool {
    if constexpr (kCountStats) {
      assert(stats != nullptr);

      ++stats->comparisons;
    }

    return std::invoke(comp, l, r);
  };

  auto swap_at = [&](std::size_t l, std::size_t r) {
    if constexpr (kCountStats) {
      assert(stats != nullptr);

      ++stats->swaps;
    }

    std::ranges::swap(data[l], data[r]);
  };

  // Sift Function
  auto sift_down = [&](std::size_t root, std::size_t heap_size) {
    while (root < heap_size / 2) {
      const std::size_t left = 2 * root + 1;
      const std::size_t right = left + 1;

      std::size_t best = root;

      if (compare(data[best], data[left]))
        best = left;

      if (right < heap_size && compare(data[best], data[right]))
        best = right;

      if (best == root)
        break;

      swap_at(root, best);
      root = best;
    }
  };

  // Build Heap
  for (std::size_t parent = data.size() / 2; parent > 0; --parent) sift_down(parent - 1, data.size());

  // Sort Heap
  for (std::size_t heap_size = data.size(); heap_size > 1; --heap_size) {
    swap_at(0, heap_size - 1);
    sift_down(0, heap_size - 1);
  }
}

// TODO: Nereikia sito kaip suprantu
// void quicksort_middle(std::vector<int>& data);
// void quicksort_median(std::vector<int>& data);
// void shellsort_sedgewick(std::vector<int>& data);
// void shellsort_ciura(std::vector<int>& data);
// void mergesort(std::vector<int>& data);
// void timsort(std::vector<int>& data);

};
