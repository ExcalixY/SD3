#include <algorithm>
#include <cstddef>
#include <optional>
#include <random>
#include <vector>

#include "duomenys.hpp"

namespace sd3 {

template <typename T>
std::vector<T> generate_many_duplicates(std::size_t size, std::optional<std::size_t> seed) {
  std::vector<T> data;
  data.reserve(size);

  std::size_t different = size / 100;
  if (different == 0)
    different++;

  for (std::size_t i = 0; i < size; ++i) data.push_back(static_cast<T>((i % different) + 1));

  std::mt19937 generator(seed.value_or(std::random_device{}()));
  std::ranges::shuffle(data, generator);

  return data;
}

template std::vector<unsigned int> generate_many_duplicates<unsigned int>(std::size_t, std::optional<std::size_t>);
template std::vector<int> generate_many_duplicates<int>(std::size_t, std::optional<std::size_t>);

}  // namespace sd3
