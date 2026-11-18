#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <utility>

#include "duomenys.hpp"

TEST_CASE("generate_nearly_sorted is ordered except for the last two elements", "[duomenys]") {
  auto const n = GENERATE(
    0u, 1u, 2u, 5u, 10u, 10'000u, 100'000u, 1'000'000u, 2'000'000u, 4'000'000u, 8'000'000u, 16'000'000u, 32'000'000u
  );

  auto list = sd3::generate_nearly_sorted(n);

  REQUIRE(list.size() == n);

  if (n >= 2) {
    REQUIRE(std::is_sorted(list.begin(), list.end() - 2));
    REQUIRE(list[n - 1] < list[n - 2]);

    // Swapping the last two back should make the whole list sorted.
    auto fixed = list;
    std::swap(fixed[n - 2], fixed[n - 1]);
    REQUIRE(std::is_sorted(fixed.begin(), fixed.end()));
  } else {
    REQUIRE(std::is_sorted(list.begin(), list.end()));
  }
}
