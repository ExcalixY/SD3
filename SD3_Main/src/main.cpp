#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <print>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

#include "helper.hpp"

struct DataKind {
  int id;
  std::string_view folder;
  std::string_view label;
  int variants;
};

constexpr DataKind kKinds[] = {
  {1, "Atsitiktiniai", "Atsitiktiniai skaičiai", 5},
  {2, "BeveikSurusiuota", "Beveik surūšiuoti", 1},
  {3, "Atvirkstine", "Atvirkščiai surūšiuoti", 1},
  {4, "DaugPasikartojanciu", "Daug pasikartojančių", 5},
};

std::filesystem::path FilePath(std::size_t millions, const DataKind& kind, int file, bool binary) {
  const std::string name = std::to_string(millions) + "mil-" + std::to_string(kind.id) + "_" +
                           std::to_string(file) + (binary ? ".bin" : ".txt");
  return std::filesystem::path(kind.folder) / name;
}

template <typename T>
std::vector<T> ReadBinary(const std::filesystem::path& path, std::size_t count) {
  static_assert(std::is_integral_v<T> && sizeof(T) == 4, "binary input requires a 32-bit integer type");

  std::ifstream input(path, std::ios::binary);
  if (!input) throw std::runtime_error("nepavyko atidaryti " + path.string());

  std::vector<T> data(count);
  const auto expected = static_cast<std::streamsize>(count * sizeof(T));
  input.read(reinterpret_cast<char*>(data.data()), expected);

  if (input.gcount() != expected) throw std::runtime_error("failas per trumpas: " + path.string());

  return data;
}

template <typename T>
void RunTests(bool binary) {
  constexpr int kRuns = 7;
  constexpr std::string_view kSeparator = "-----------------------------------------------------";

  for (std::size_t millions = 2; millions <= 32; millions *= 2) {
    const std::size_t count = millions * 1'000'000;

    std::println("{}", kSeparator);
    std::println("Aibės dydis: {}\n", count);

    for (const DataKind& kind : kKinds) {
      uint64_t comparisons = 0;
      uint64_t swaps = 0;
      std::chrono::milliseconds time{0};

      std::println("Tipas: {}:", kind.label);

      for (int file = 1; file <= kind.variants; ++file) {
        const std::filesystem::path path = FilePath(millions, kind, file, binary);

        if (!std::filesystem::exists(path)) throw std::runtime_error("nerastas failas: " + path.string());

        std::println("\tRūšiuojamas: {}", path.filename().string());

        const std::vector<T> data = binary ? ReadBinary<T>(path, count)
                                           : sd3::GenerateFromFile<T>(path.string(), count);

        for (int run = 0; run < kRuns; ++run) {
          auto [stats, elapsed] = sd3::MeasureHeapsortSlow(data);

          comparisons += stats.comparisons;
          swaps += stats.swaps;
          time += elapsed;
        }
      }

      const double total = static_cast<double>(kind.variants * kRuns);

      std::println("Rezultatas:");
      std::println("\tLaikas (avg. ms): {}", static_cast<double>(time.count()) / total);
      std::println("\tPalyginimai (avg. count): {}", static_cast<double>(comparisons) / total);
      std::println("\tSukeitimai (avg. count): {}", static_cast<double>(swaps) / total);
      std::println();
    }
  }
}

int main(int argc, char** argv) {
  bool binary = false;
  bool signed_mode = false;

  for (int i = 1; i < argc; ++i) {
    if (std::strcmp(argv[i], "--bin") == 0) {
      binary = true;
    } else if (std::strcmp(argv[i], "--signed") == 0) {
      signed_mode = true;
    } else {
      std::println("Naudojimas: {} [--bin] [--signed]", argv[0]);
      return 1;
    }
  }

  try {
    if (signed_mode)
      RunTests<std::int32_t>(binary);
    else
      RunTests<unsigned int>(binary);
  } catch (const std::exception& error) {
    std::println("klaida: {}", error.what());
    return 1;
  }

  return 0;
}
