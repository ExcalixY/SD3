#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <cstddef>

#include "duomenys.hpp"

TEST_CASE("generate_many_duplicates has 1% unique items", "[duomenys]") {
  auto const n = GENERATE(10'000u, 100'000u, 1'000'000u, 2'000'000u, 4'000'000u, 8'000'000u, 16'000'000u, 32'000'000u);

  auto list = sd3::generate_many_duplicates(n);

  REQUIRE(list.size() == n);

  auto sorted = list;
  std::sort(sorted.begin(), sorted.end());
  auto const uniqueCount = static_cast<std::size_t>(std::unique(sorted.begin(), sorted.end()) - sorted.begin());

  REQUIRE(uniqueCount == std::max<std::size_t>(1, n / 100));
}
