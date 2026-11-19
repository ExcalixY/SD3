#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <cstdint>

#include "duomenys.hpp"

TEST_CASE("generate_random produces unpredictable data of the requested size", "[duomenys]") {
  auto const n = GENERATE(
    0u, 1u, 2u, 5u, 10u, 10'000u, 100'000u, 1'000'000u, 2'000'000u, 4'000'000u, 8'000'000u, 16'000'000u, 32'000'000u
  );

  auto list = sd3::generate_random(n);

  REQUIRE(list.size() == n);

  // A fixed seed makes the output reproducible
  if (n <= 10'000) {
    REQUIRE(sd3::generate_random(n, 42) == sd3::generate_random(n, 42));
  }
}

TEST_CASE("generate_random<std::int32_t> produces reproducible signed values", "[duomenys]") {
  const auto list = sd3::generate_random<std::int32_t>(10'000, 42);

  REQUIRE(list.size() == 10'000);
  REQUIRE(std::any_of(list.begin(), list.end(), [](std::int32_t value) { return value < 0; }));
  REQUIRE(list == sd3::generate_random<std::int32_t>(10'000, 42));
}
