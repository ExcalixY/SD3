#pragma once

#include <chrono>
#include <cstddef>
#include <fstream>
#include <functional>
#include <string>
#include <utility>
#include <vector>

#include "algoritmai.hpp"

namespace sd3 {

template <typename T>
std::pair<SortStats, std::chrono::milliseconds> MeasureHeapsort(const std::vector<T>& data) {
  SortStats stats{};

  std::vector<T> data_counted = data;
  std::vector<T> data_timed = data;

  // Measure operations per second
  sd3::heapsort<true>(data_counted, std::less<>{}, &stats);

  auto time_pre = std::chrono::high_resolution_clock::now();

  // Measure time
  sd3::heapsort(data_timed);

  auto time_post = std::chrono::high_resolution_clock::now();

  return {stats, std::chrono::duration_cast<std::chrono::milliseconds>(time_post - time_pre)};
}

template <typename T>
std::pair<SortStats, std::chrono::milliseconds> MeasureHeapsortSlow(const std::vector<T>& data) {
  SortStats stats{};

  std::vector<T> data_counted = data;

  auto time_pre = std::chrono::high_resolution_clock::now();

  sd3::heapsort<true>(data_counted, std::less<>{}, &stats);

  auto time_post = std::chrono::high_resolution_clock::now();

  return {stats, std::chrono::duration_cast<std::chrono::milliseconds>(time_post - time_pre)};
}

template <typename T>
std::vector<T> GenerateFromFile(const std::string& filepath, std::size_t n) {
  std::vector<T> vec(n);

  std::ifstream input(filepath);

  for (std::size_t i = 0; i < n; i++) {
    T temp;
    input >> temp;

    vec[i] = temp;
  }

  return vec;
}

}
