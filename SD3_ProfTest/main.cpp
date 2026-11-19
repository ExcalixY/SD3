#include <cstdint>
#include <filesystem>
#include <fstream>
#include <print>
#include <vector>

#include "algoritmai.hpp"
#include "helper.hpp"

int main(int argc, char* argv[]) {
  const std::filesystem::path path = std::filesystem::absolute(argv[0]).parent_path() / "2mil-1.txt";

  std::ifstream input(path);
  if (!input) {
    std::println("klaida: nepavyko atidaryti {}", path.string());
    return 1;
  }

  // Professor's dataset holds unsigned 32-bit values (up to ~4.29e9), which do not fit in int.
  std::vector<std::uint32_t> list;
  list.reserve(2'000'000);

  std::uint64_t value = 0;
  while (input >> value) list.push_back(static_cast<std::uint32_t>(value));

  if (list.size() < 2) {
    std::println("klaida: nepakanka duomenų faile: {}", path.string());
    return 1;
  }

  auto [stats, time] = sd3::MeasureHeapsortSlow(list);

  std::println("Laikas: {}", time.count());
  std::println("Palyginimai: {}", stats.comparisons);
  std::println("Sukeitimai: {}", stats.swaps);

  return 0;
}
