#pragma once

#include <chrono>
#include <vector>

namespace sd3 {

template <typename TFunc, typename T>
auto MeasureAlgorithm(TFunc&& algorithm, std::vector<T>& data) {
  auto time_pre = std::chrono::high_resolution_clock::now();

  algorithm(data);

  auto time_post = std::chrono::high_resolution_clock::now();

  return std::chrono::duration_cast<std::chrono::milliseconds>(time_post - time_pre);
}

}
