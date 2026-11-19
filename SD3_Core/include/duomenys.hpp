#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <vector>

namespace sd3 {

// Only unsigned int and std::int32_t are explicitly instantiated (see src/duomenys/*.cpp).
// Any other T is declared but left undefined and will fail at link time.

template <typename T = unsigned int>
std::vector<T> generate_random(std::size_t size, std::optional<std::size_t> seed = std::nullopt);

template <typename T = unsigned int>
std::vector<T> generate_reversed(std::size_t size, std::optional<std::size_t> seed = std::nullopt);

template <typename T = unsigned int>
std::vector<T> generate_nearly_sorted(std::size_t size, std::optional<std::size_t> seed = std::nullopt);

template <typename T = unsigned int>
std::vector<T> generate_many_duplicates(std::size_t size, std::optional<std::size_t> seed = std::nullopt);

// TODO: Nereikia situ kaip suprantu
// std::vector<int> generate_sorted_runs(
//   std::size_t size, std::size_t run_count = 32, std::optional<std::size_t> seed = std::nullopt
// );
// std::vector<int> generate_periodic(
//   std::size_t size, std::size_t period, std::optional<std::size_t> seed = std::nullopt
// );

}  // namespace sd3
