#pragma once

#include <cstddef>
#include <vector>

namespace sd3 {

std::vector<int> generate_random(std::size_t size);
std::vector<int> generate_nearly_sorted(std::size_t size);
std::vector<int> generate_reversed(std::size_t size);
std::vector<int> generate_many_duplicates(std::size_t size);
std::vector<int> generate_sorted_runs(std::size_t size, std::size_t run_count = 32);
std::vector<int> generate_periodic(std::size_t size, std::size_t period);

}
