# SD3

Rūšiavimo algoritmo Heapsort eksperimentinis palyginimas su skirtingų tipų pradiniais duomenimis.

## Reikalavimai

- **CMake 4.0+**
- **Ninja**
- C++23 kompiliatorius: GCC 14+ / Clang 17+ (Linux, macOS) arba MSVC iš Visual Studio 2022+ (Windows)

Catch2 (testams) atsisiunčiamas automatiškai pirmojo konfigūravimo metu, todėl vieną kartą reikia interneto ryšio.

## Presetai

Visi kompiliavimo nustatymai yra `CMakePresets.json` faile. Kiekviena OS mato tik savo presetus:

| Presetas       | Paskirtis                                                  |
| -------------- | ---------------------------------------------------------- |
| `{os}-debug`   | Debug versija programavimui                                |
| `{os}-release` | Optimizuota versija. **Naudokite laiko matavimams.**       |
| `{os}-testing` | Debug informacija + AddressSanitizer/UBSan, testų leidimui |

`{os}` – `linux`, `darwin` (macOS) arba `windows`.

Kompiliavimo failai saugomi `build/{preset}/`, vykdomieji failai – `out/{OS}-{BuildType}/bin/` (`SD3` ir `SD3_Test`).

Asmeniniams nustatymams susikurkite `CMakeUserPresets.json` (jis įtrauktas į `.gitignore`), o ne redaguokite `CMakePresets.json`.

## Terminalas su CMake

```bash
cmake --preset linux-release
cmake --build --preset linux-release
./out/Linux-Release/bin/SD3
```

Sukonfigūruoti, sukompiliuoti ir paleisti visus testus vienu žingsniu:

```bash
cmake --workflow --preset linux-testing
```

Windows sistemoje šias komandas leiskite iš **Developer PowerShell / Developer Command Prompt for VS**, kad būtų randamas `cl`, ir naudokite `windows-*` presetus.

> Pridėję naują `.cpp` failą, iš naujo paleiskite `cmake --preset {preset}`, nes šaltinio failai surenkami per glob.

## Visual Studio

1. **File → Open → Folder…** ir pasirinkite projekto aplanką. `.sln` failo generuoti nereikia – VS `CMakePresets.json` nuskaito tiesiogiai.
2. Įrankių juostos konfigūracijų sąraše pasirinkite presetą (`windows-debug`, `windows-release` arba `windows-testing`).
3. Kaip paleidžiamąjį elementą (startup item) pasirinkite `SD3.exe` ir spauskite **F5** – programa bus sukompiliuota ir paleista.
4. Testai rodomi **Test → Test Explorer** lange.

Jei VS skundžiasi dėl CMake versijos, vadinasi, kartu su juo įdiegtas CMake yra senesnis nei 4.0. Įdiekite naujesnį CMake ir nurodykite jį VS, pavyzdžiui, lauku `"cmakeExecutable"` konfigūravimo presete savo `CMakeUserPresets.json` faile.

## CLion

1. **File → Open** ir pasirinkite projekto aplanką.
2. CLion presetus importuoja kaip CMake profilius. Norimus profilius įjunkite **Settings → Build, Execution, Deployment → CMake**.
3. Įrankių juostoje pasirinkite profilį ir `SD3` arba `SD3_Test` paleidimo konfigūraciją, tada spauskite **Run**.

Pastabos:

- Jei kartu su CLion pateikiamas CMake yra senesnis nei 4.0, **Settings → Build, Execution, Deployment → Toolchains** pasirinkite sistemoje įdiegtą CMake.
- Windows sistemoje naudokite **Visual Studio** įrankių rinkinį (toolchain), o ne MinGW, nes presetai naudoja MSVC.
- Pridėję naują failą, spauskite **File → Reload CMake Project**.
- Prie kiekvieno Catch2 `TEST_CASE` redaktoriaus paraštėje atsiranda paleidimo mygtukas.

## Projekto struktūra

```
include/algoritmai.hpp   rūšiavimo algoritmų deklaracijos
include/duomenys.hpp     duomenų generatorių deklaracijos
src/algoritmai/          po vieną failą kiekvienam rūšiavimo algoritmui
src/duomenys/            po vieną failą kiekvienam duomenų generatoriui
src/main.cpp             eksperimentų paleidimo programa
test/                    Catch2 testai (algoritmai/, duomenys/)
```

## Atlikti darbai

1. Marija - Aprašas
2. Vincas - Atsitiktinis ir Atvirkštinis
3. Ugnius - Daug Pasikartojančių ir Beveik Surušiuotas
4. Renaldas - Heapsort ir Testai
