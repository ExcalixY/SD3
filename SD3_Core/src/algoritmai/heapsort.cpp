#include <concepts>
#include <cstddef>
#include <vector>

#include "algoritmai.hpp"

namespace sd3 {

void heapsort(std::vector<unsigned int>& data, SortStats& stats) {
  if (data.size() < 2) {
    return;
  }

  auto compare = [&](const unsigned int l, const unsigned int r) -> bool {
    ++stats.comparisons;
    return l < r;
  };

  auto swap_at = [&](std::size_t l, std::size_t r) {
    ++stats.swaps;
    std::ranges::swap(data[l], data[r]);
  };

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

  for (std::size_t parent = data.size() / 2; parent > 0; --parent) sift_down(parent - 1, data.size());

  for (std::size_t heap_size = data.size(); heap_size > 1; --heap_size) {
    swap_at(0, heap_size - 1);
    sift_down(0, heap_size - 1);
  }
}

}
