#include <charconv>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <type_traits>
#include <vector>

#include "duomenys.hpp"

namespace {

constexpr std::size_t kSizes[] = {2, 4, 8, 16, 32};

template <typename T>
using Generator = std::vector<T> (*)(std::size_t, std::optional<std::size_t>);

template <typename T>
struct Kind {
  int id;
  std::string_view directory;
  std::size_t variants;
  Generator<T> generate;
};

template <typename T>
constexpr Kind<T> kKinds[] = {
  {1, "Atsitiktiniai", 5, sd3::generate_random<T>},
  {2, "BeveikSurusiuota", 1, sd3::generate_nearly_sorted<T>},
  {3, "Atvirkstine", 1, sd3::generate_reversed<T>},
  {4, "DaugPasikartojanciu", 5, sd3::generate_many_duplicates<T>},
};

void PrintUsage(std::string_view program) {
  std::cout << "Usage: " << program << " [--bin] [--signed] [--seed N]\n"
            << "  --bin     -> write raw 32-bit ints instead of text (default: text)\n"
            << "  --signed  -> generate signed (int32_t) values instead of unsigned\n"
            << "  --seed N  -> base seed (default: time-based); variants use N, N+1, ...\n"
            << "Generates all four types for 2/4/8/16/32mil:\n"
            << "  Atsitiktiniai/[n]mil-1_[a].txt       (random, 5 files)\n"
            << "  BeveikSurusiuota/[n]mil-2_1.txt      (nearly sorted)\n"
            << "  Atvirkstine/[n]mil-3_1.txt           (reverse sorted)\n"
            << "  DaugPasikartojanciu/[n]mil-4_[a].txt (many duplicates, 5 files)\n";
}

bool ParseArgs(int argc, char* argv[], bool& binary, bool& signed_mode, std::optional<std::size_t>& seed) {
  for (int i = 1; i < argc; ++i) {
    const std::string_view arg(argv[i]);

    if (arg == "--bin") {
      binary = true;
      continue;
    }

    if (arg == "--signed") {
      signed_mode = true;
      continue;
    }

    if (arg == "--seed") {
      if (++i >= argc) return false;
      const std::string_view text(argv[i]);
      std::size_t value = 0;
      auto [end, ec] = std::from_chars(text.data(), text.data() + text.size(), value);
      if (ec != std::errc{} || end != text.data() + text.size()) return false;
      seed = value;
      continue;
    }

    if (arg.starts_with("--seed=")) {
      const std::string_view text = arg.substr(7);
      std::size_t value = 0;
      auto [end, ec] = std::from_chars(text.data(), text.data() + text.size(), value);
      if (ec != std::errc{} || end != text.data() + text.size()) return false;
      seed = value;
      continue;
    }

    return false;
  }

  return true;
}

template <typename T>
void WriteText(const std::filesystem::path& path, const std::vector<T>& data) {
  static_assert(std::is_integral_v<T> && sizeof(T) == 4, "text output requires a 32-bit integer type");

  std::ofstream out(path, std::ios::binary);
  if (!out) throw std::runtime_error("could not open " + path.string() + " for writing");

  std::string buffer;
  buffer.reserve(1 << 20);

  for (T value : data) {
    char number[16];
    auto [end, ec] = std::to_chars(number, number + sizeof(number), value);
    if (ec != std::errc{}) throw std::runtime_error("could not format a number");

    const std::size_t length = static_cast<std::size_t>(end - number);
    if (buffer.size() + length + 1 > buffer.capacity()) {
      out.write(buffer.data(), static_cast<std::streamsize>(buffer.size()));
      buffer.clear();
    }

    buffer.append(number, end);
    buffer.push_back('\n');
  }

  if (!buffer.empty()) out.write(buffer.data(), static_cast<std::streamsize>(buffer.size()));

  out.flush();
  if (!out) throw std::runtime_error("failed while writing " + path.string());
}

template <typename T>
void WriteBinary(const std::filesystem::path& path, const std::vector<T>& data) {
  static_assert(std::is_integral_v<T> && sizeof(T) == 4, "binary output requires a 32-bit integer type");

  std::ofstream out(path, std::ios::binary);
  if (!out) throw std::runtime_error("could not open " + path.string() + " for writing");

  if (!data.empty()) {
    out.write(reinterpret_cast<const char*>(data.data()),
              static_cast<std::streamsize>(data.size() * sizeof(T)));
  }

  out.flush();
  if (!out) throw std::runtime_error("failed while writing " + path.string());
}

template <typename T>
void RunGeneration(bool binary, std::size_t base_seed) {
  for (const Kind<T>& kind : kKinds<T>) {
    std::filesystem::create_directories(kind.directory);

    for (std::size_t millions : kSizes) {
      for (std::size_t file = 1; file <= kind.variants; ++file) {
        const std::string name = std::to_string(millions) + "mil-" + std::to_string(kind.id) + "_" +
                                 std::to_string(file) + (binary ? ".bin" : ".txt");
        const std::filesystem::path path = std::filesystem::path(kind.directory) / name;

        std::cout << "Generating " << path.string() << " ... " << std::flush;
        const std::vector<T> data = kind.generate(millions * 1'000'000, base_seed + file - 1);

        if (binary)
          WriteBinary<T>(path, data);
        else
          WriteText<T>(path, data);

        std::cout << "done (" << data.size() << " values)\n";
      }
    }
  }
}

}  // namespace

int main(int argc, char* argv[]) {
  bool binary = false;
  bool signed_mode = false;
  std::optional<std::size_t> seed = std::nullopt;

  if (!ParseArgs(argc, argv, binary, signed_mode, seed)) {
    PrintUsage(argv[0]);
    return 1;
  }

  const std::size_t base_seed =
    seed.value_or(static_cast<std::size_t>(std::chrono::steady_clock::now().time_since_epoch().count()));

  try {
    if (signed_mode)
      RunGeneration<std::int32_t>(binary, base_seed);
    else
      RunGeneration<unsigned int>(binary, base_seed);
  } catch (const std::exception& error) {
    std::cerr << "error: " << error.what() << '\n';
    return 1;
  }

  return 0;
}
