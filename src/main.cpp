#include <chrono>
#include <cstddef>
#include <cstdint>
#include <print>
#include <vector>

#include "algoritmai.hpp"
#include "duomenys.hpp"
#include "helper.hpp"

uint64_t comparison_count = 0;
uint64_t swap_count = 0;
std::chrono::milliseconds time_count;

void PrintAndResetCounters(int n, int m) {
  double count = static_cast<double>(n * m);

  std::println("\tLaikas (avg. ms): {}", (time_count / count).count());
  std::println("\tPalyginimai (avg. count): {}", static_cast<double>(comparison_count) / count);
  std::println("\tSukeitimai (avg. count): {}", static_cast<double>(swap_count) / count);

  comparison_count = 0;
  swap_count = 0;
  time_count = std::chrono::milliseconds::zero();
}

int main(int argc, char* argv[]) {
  for (std::size_t i = 2; i <= 32; i *= 2) {
    std::size_t l = i * 1000000;
    std::println("----------------------------------------------");

    std::println("Aibės dydis: {}\n", l);

    std::println("Atsitiktiniai skaičiai [5 aibės | 7 kartai]:");

    comparison_count = 0;
    swap_count = 0;
    time_count = std::chrono::milliseconds::zero();

    std::vector<int> data;

    // Random Numbers
    for (std::size_t n = 0; n < 5; ++n) {
      data = sd3::generate_random(l);

      for (std::size_t m = 0; m < 7; ++m) {
        auto [stats, time] = sd3::MeasureHeapsort(data);

        comparison_count += stats.comparisons;
        swap_count += stats.swaps;
        time_count += time;
      }
    }
    PrintAndResetCounters(5, 7);

    std::println("Atvirkščiai surūšiuoti: [1 aibės | 7 kartai]:");
    // Reverse Sorted
    data = sd3::generate_reversed(l);
    for (std::size_t m = 0; m < 7; ++m) {
      auto [stats, time] = sd3::MeasureHeapsort(data);

      comparison_count += stats.comparisons;
      swap_count += stats.swaps;
      time_count += time;
    }
    PrintAndResetCounters(1, 7);

    std::println("Beveik surūšiuoti: [1 aibės | 7 kartai]:");
    // Nearly Sorted
    data = sd3::generate_nearly_sorted(l);
    for (std::size_t m = 0; m < 7; ++m) {
      auto [stats, time] = sd3::MeasureHeapsort(data);

      comparison_count += stats.comparisons;
      swap_count += stats.swaps;
      time_count += time;
    }
    PrintAndResetCounters(1, 7);

    std::println("Daug pasikartojančių: [5 aibės | 7 kartai]:");
    // Many Duplicated
    for (std::size_t n = 0; n < 5; ++n) {
      data = sd3::generate_many_duplicates(l);

      for (std::size_t m = 0; m < 7; ++m) {
        auto [stats, time] = sd3::MeasureHeapsort(data);

        comparison_count += stats.comparisons;
        swap_count += stats.swaps;
        time_count += time;
      }
    }
    PrintAndResetCounters(5, 7);
  }

  return 0;
}
