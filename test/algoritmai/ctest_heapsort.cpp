#include <algorithm>
#include <array>
#include <catch2/catch_test_macros.hpp>
#include <functional>
#include <vector>

#include "algoritmai.hpp"

TEST_CASE("heapsort sorts elements in ascending order", "[algoritmai]") {
  SECTION("typical unsorted input") {
    std::vector<int> data{5, 2, 9, 1, 7, 3, 8, 4, 6};
    sd3::heapsort(data);
    REQUIRE(std::ranges::is_sorted(data));
  }

  SECTION("empty and single-element ranges") {
    std::vector<int> empty;
    sd3::heapsort(empty);
    REQUIRE(empty.empty());

    std::vector<int> single{42};
    sd3::heapsort(single);
    REQUIRE(single == std::vector<int>{42});
  }

  SECTION("already sorted") {
    std::vector<int> data{1, 2, 3, 4, 5, 6};
    sd3::heapsort(data);
    REQUIRE(std::ranges::is_sorted(data));
  }

  SECTION("reverse sorted") {
    std::vector<int> data{6, 5, 4, 3, 2, 1};
    sd3::heapsort(data);
    REQUIRE(std::ranges::is_sorted(data));
  }

  SECTION("all duplicates") {
    std::vector<int> data{7, 7, 7, 7, 7};
    sd3::heapsort(data);
    REQUIRE(data == std::vector<int>{7, 7, 7, 7, 7});
  }

  SECTION("negative numbers") {
    std::vector<int> data{0, -5, 3, -1, -9, 2};
    sd3::heapsort(data);
    REQUIRE(data == std::vector<int>{-9, -5, -1, 0, 2, 3});
  }

  SECTION("larger input") {
    std::vector<int> data(1'000);
    for (int i = 0; i < 1'000; ++i) {
      data[i] = 1'000 - i;
    }

    sd3::heapsort(data);

    REQUIRE(std::ranges::is_sorted(data));
    REQUIRE(data.front() == 1);
    REQUIRE(data.back() == 1'000);
  }

  SECTION("any contiguous range works") {
    std::array<int, 6> data{4, 2, 5, 1, 3, 0};
    sd3::heapsort(data);
    REQUIRE(std::ranges::is_sorted(data));
  }
}

TEST_CASE("heapsort honors a custom comparator", "[algoritmai]") {
  std::vector<int> data{3, 1, 4, 1, 5, 9, 2, 6};
  sd3::heapsort(data, std::greater<>{});
  REQUIRE(std::ranges::is_sorted(data, std::greater<>{}));
}

TEST_CASE("heapsort can count comparisons and swaps", "[algoritmai]") {
  std::vector<int> data{5, 4, 3, 2, 1};
  sd3::SortStats stats;
  sd3::heapsort<true>(data, std::less<>{}, &stats);

  REQUIRE(std::ranges::is_sorted(data));
  REQUIRE(stats.comparisons > 0);
  REQUIRE(stats.swaps > 0);
}
