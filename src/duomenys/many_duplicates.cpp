#include <unistd.h>


#include <cstddef>
#include <optional>
#include <vector>

#include "duomenys.hpp"

namespace sd3 {

std::vector<int> generate_many_duplicates(std::size_t size, std::optional<std::size_t> seed) {
  std::vector<int> duplicatesArray;
  duplicatesArray.reserve(size);

  size_t different = (size / 100);
  if (different == 0)
    different++;

  for (std::size_t i = 0; i < size; ++i) {
    duplicatesArray.push_back(((i%different)+1));
  }

  return duplicatesArray;
}

}
