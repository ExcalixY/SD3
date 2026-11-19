#include <algorithm>
#include <chrono>
#include <cstddef>
#include <limits>
#include <optional>
#include <random>
#include <vector>

#include "duomenys.hpp"

namespace sd3 {

template <typename T>
std::vector<T> generate_reversed(std::size_t size, std::optional<std::size_t> seed) {
  const std::size_t actual_seed =
    seed.value_or(static_cast<std::size_t>(std::chrono::steady_clock::now().time_since_epoch().count()));

  std::default_random_engine randomNumberGenerator(actual_seed);
  std::uniform_int_distribution<int> distribution(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

  std::vector<T> data;
  data.reserve(size);

  for (std::size_t i = 0; i < size; ++i) data.push_back(static_cast<T>(distribution(randomNumberGenerator)));

  std::sort(data.rbegin(), data.rend());
  return data;
}

template std::vector<unsigned int> generate_reversed<unsigned int>(std::size_t, std::optional<std::size_t>);
template std::vector<int> generate_reversed<int>(std::size_t, std::optional<std::size_t>);

}  // namespace sd3
