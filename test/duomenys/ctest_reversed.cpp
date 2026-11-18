#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <cstddef>
#include <functional>

#include "duomenys.hpp"

TEST_CASE("generate_reversed is sorted from highest to lowest", "[duomenys]") {
  auto const n = GENERATE(
    0u, 1u, 2u, 5u, 10u, 10'000u, 100'000u, 1'000'000u, 2'000'000u, 4'000'000u, 8'000'000u, 16'000'000u, 32'000'000u
  );

  auto list = sd3::generate_reversed(n);

  REQUIRE(list.size() == n);
  REQUIRE(std::is_sorted(list.begin(), list.end(), std::greater<>{}));
}
