#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <cstddef>

#include "duomenys.hpp"

TEST_CASE("generate_many_duplicates has at most 1% unique items", "[duomenys]") {
  auto const n = GENERATE(
    0u, 1u, 2u, 5u, 10u, 10'000u, 100'000u, 1'000'000u, 2'000'000u, 4'000'000u, 8'000'000u, 16'000'000u, 32'000'000u
  );

  auto list = sd3::generate_many_duplicates(n);

  REQUIRE(list.size() == n);

  // Sort a copy to count distinct values without a memory-hungry std::set.
  auto sorted = list;
  std::sort(sorted.begin(), sorted.end());
  auto const uniqueCount = static_cast<std::size_t>(std::unique(sorted.begin(), sorted.end()) - sorted.begin());

  // For n < 100 a single distinct value is the closest possible result to 1%.
  REQUIRE(uniqueCount <= std::max<std::size_t>(1, n / 100));
}
