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

Kompiliavimo failai saugomi `build/{preset}/`, vykdomieji failai – `out/{OS}-{BuildType}/bin/`: `SD3_Generate`, `SD3`, `SD3_Test` ir `SD3_ProfTest`.

Asmeniniams nustatymams susikurkite `CMakeUserPresets.json` (jis įtrauktas į `.gitignore`), o ne redaguokite `CMakePresets.json`.

## Terminalas su CMake

```bash
cmake --preset linux-release
cmake --build --preset linux-release
```

Sukonfigūruoti, sukompiliuoti ir paleisti visus testus vienu žingsniu:

```bash
cmake --workflow --preset linux-testing
```

Windows sistemoje šias komandas leiskite iš **Developer PowerShell / Developer Command Prompt for VS**, kad būtų randamas `cl`, ir naudokite `windows-*` presetus.

> Pridėję naują `.cpp` failą, iš naujo paleiskite `cmake --preset {preset}`, nes šaltinio failai surenkami per glob.

## Darbo eiga

Visi vykdomieji failai yra `out/{OS}-{BuildType}/bin/`. Įprasta tvarka:

**1. Sugeneruoti duomenis – `SD3_Generate`.** Sukuria failus keturiems duomenų tipams ir penkiems dydžiams (2, 4, 8, 16, 32 mln.) kataloguose `Atsitiktiniai/`, `BeveikSurusiuota/`, `Atvirkstine/`, `DaugPasikartojanciu/`. Failų vardai: `[n]mil-[m]_[a].[txt|bin]`.

```bash
cd out/Linux-Release/bin
./SD3_Generate
```

| Parinktis  | Paskirtis                                                         |
| ---------- | ----------------------------------------------------------------- |
| `--bin`    | rašyti dvejetainius failus (vietoje tekstinių, numatytasis – txt) |
| `--signed` | generuoti `int32_t` reikšmes (numatytasis tipas – `unsigned int`) |
| `--seed N` | generatoriaus pradinė sėkla (kiekvienas failas gauna N, N+1, …)   |

**2. Atlikti matavimus – `SD3`.** Paleiskite **tame pačiame kataloge**, kuriame `SD3_Generate` sukūrė duomenų katalogus. Programa rūšiuoja kiekvieną failą po 7 kartų ir išveda vidutinius laiko, palyginimų bei sukeitimų skaičius, sugrupuotus pagal tipą.

```bash
./SD3             # tekstiniai failai (numatytasis variantas)
./SD3 --bin       # dvejetainiai failai
./SD3 --signed    # signed (int32_t) failai
```

**3. Patikrinti, ar viskas tvarkoje – `SD3_Test`.** Catch2 testai tikrina rūšiavimo algoritmą ir duomenų generatorius; juos galima paleisti ir per CTest (žr. skyrių „Testai“).

```bash
./SD3_Test
```

**4. Palyginti su dėstytojo failu – `SD3_ProfTest`.** Įdėkite dėstytojo atsiųstą `2mil-1.txt` šalia vykdomojo failo ir paleiskite:

```bash
cp ~/Downloads/2mil-1.txt .
./SD3_ProfTest
```

Programa nuskaito failą kaip `uint32_t`, rūšiuoja jį ir spausdina laiką, palyginimų ir sukeitimų skaičius – jie turi atitikti dėstytojo pateiktus rezultatus.

Trumpai: `SD3_Generate` → `SD3`, o `SD3_Test` ir `SD3_ProfTest` tikrina atitinkamai vidinę logiką ir rezultatą su dėstytojo duomenimis.

## Testai

Testai rašomi su **Catch2** ir per `catch_discover_tests` automatiškai užregistruojami CTest'e – kiekvienas `TEST_CASE` rodomas kaip atskiras testas. Registruojant pridedamos parinktys `--success` ir `--durations yes`, todėl `ctest -V` iškart rodo teiginius ir vykdymo trukmes. Šaltiniai: `test/algoritmai/` (rūšiavimas) ir `test/duomenys/` (duomenų generatoriai).

Paleisti visus testus:

```bash
ctest --preset linux-testing
# arba nurodant build katalogą:
ctest --test-dir build/linux-testing --output-on-failure
```

Testus galima filtruoti pagal pavadinimą arba paleisti tiesiogiai per `SD3_Test`, kad gautumėte išsamesnę Catch2 išvestį:

```bash
ctest --test-dir build/linux-testing -R heapsort -V   # tik "heapsort" testai, visa išvestis
./out/Linux-Debug/bin/SD3_Test "[algoritmai]"         # pagal žymą
./out/Linux-Debug/bin/SD3_Test "[duomenys]" -s -d yes # sėkmingi teiginiai + trukmės
./out/Linux-Debug/bin/SD3_Test --list-tests            # testų sąrašas
```

Naudingos `Catch2` parinktys:

| Parinktis          | Paskirtis                                                                 |
| ------------------ | ------------------------------------------------------------------------- |
| `-s`, `--success`  | rodo ir sėkmingus `REQUIRE`/`CHECK` teiginius su išskleistomis reikšmėmis |
| `-v high`          | išsamesnė išvestis (testų ir `SECTION` informacija)                       |
| `-d yes`           | kiekvieno testo ir `SECTION` vykdymo trukmė                               |
| `-r compact`       | po vieną eilutę kiekvienam teiginiui                                      |
| `-c "pavadinimas"` | paleisti tik pasirinktą `SECTION`                                         |

Testų pavadinimai ir žymos (`[algoritmai]`, `[duomenys]`) aprašyti pačiuose `TEST_CASE` šaltiniuose. Duomenų generatorių testai tikrina 13 dydžių (nuo 0 iki 32 mln.), todėl visas ciklas užtrunka apie 35 s; kasdieniam darbui naudinga paleisti tik `[algoritmai]` arba atskirą testą pagal pavadinimą.

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
SD3_Core/                pagrindinė biblioteka
  include/               algoritmai.hpp, duomenys.hpp, helper.hpp
  src/algoritmai/        Heapsort realizacija (šaltinio failas)
  src/duomenys/          duomenų generatorių apibrėžtys
SD3_Main/                matavimų programa (vykdomasis failas SD3)
SD3_Generate/            duomenų failų generatorius (SD3_Generate)
SD3_ProfTest/            patikra su dėstytojo failu (SD3_ProfTest)
test/                    Catch2 testai (algoritmai/, duomenys/)
```

## Atlikti darbai

1. Marija - Aprašas
2. Vincas - Atsitiktinis ir Atvirkštinis
3. Ugnius - Daug Pasikartojančių ir Beveik Surušiuotas
4. Renaldas - Heapsort ir Testai
