#include <chrono>
#include <cstddef>
#include <optional>
#include <random>
#include <vector>
#include <algorithm>

#include "duomenys.hpp"

namespace sd3 {

std::vector<int> generate_reversed(std::size_t size, std::optional<std::size_t> seed) {
  

  std::size_t actual_seed = seed.value_or(
        static_cast<std::size_t>(std::chrono::steady_clock::now().time_since_epoch().count())
    );   

  
	std::default_random_engine randomNumberGenerator(actual_seed);               
	std::uniform_int_distribution<int> distribution(1, 9999999); 


  
	std::vector <int> data;

  data.reserve(size);
	for (std::size_t i = 0; i < size; i++)
		data.push_back(distribution(randomNumberGenerator));  


  
  std::sort(data.rbegin(), data.rend());
  return data; 
}

}
