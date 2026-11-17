#include <cstddef>
#include <optional>
#include <vector>

#include "duomenys.hpp"

namespace sd3 {

std::vector<int> generate_nearly_sorted(std::size_t size, std::optional<std::size_t> seed) {
  std::vector<int> nearlySortedArray;
  nearlySortedArray.reserve(size);

  if (size > static_cast<std::size_t>(std::numeric_limits<int>::max())) {}

  for (std::size_t i = 0; i < size; ++i) {
    nearlySortedArray.push_back(static_cast<int>(i+1));
  }

  if (size >= 2) {
    std::swap(nearlySortedArray[size-2], nearlySortedArray[size-1]);
  }

  return nearlySortedArray;
}

}
