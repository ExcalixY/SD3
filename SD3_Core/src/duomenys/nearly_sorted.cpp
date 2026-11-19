#include <cstddef>
#include <optional>
#include <utility>
#include <vector>

#include "duomenys.hpp"

namespace sd3 {

template <typename T>
std::vector<T> generate_nearly_sorted(std::size_t size, std::optional<std::size_t> seed) {
  (void)seed;

  std::vector<T> data;
  data.reserve(size);

  for (std::size_t i = 0; i < size; ++i) data.push_back(static_cast<T>(i + 1));

  if (size >= 2)
    std::swap(data[size - 2], data[size - 1]);

  return data;
}

template std::vector<unsigned int> generate_nearly_sorted<unsigned int>(std::size_t, std::optional<std::size_t>);
template std::vector<int> generate_nearly_sorted<int>(std::size_t, std::optional<std::size_t>);

}  // namespace sd3
