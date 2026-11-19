cmake_minimum_required(VERSION 4.0)
project(SD3
  VERSION 0.01
  DESCRIPTION "SD3 namų darbas - Marija, Vincas, Ugnius, Renaldas"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OUT_DIR
  ${CMAKE_SOURCE_DIR}/out/${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUT_DIR}/archive/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR}/bin/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUT_DIR}/lib/)

# Projekto dalys
add_subdirectory(SD3_Core)
add_subdirectory(SD3_Generate)
add_subdirectory(SD3_Main)
add_subdirectory(SD3_ProfTest)

# Testavimui
enable_testing()

include(FetchContent)
FetchContent_Declare(Catch2 GIT_REPOSITORY https://github.com/catchorg/Catch2 GIT_TAG v3.7.1)
FetchContent_MakeAvailable(Catch2)

file(GLOB_RECURSE SD3_TEST_SRC ${CMAKE_SOURCE_DIR}/test/*.cpp)

add_executable(SD3_Test ${SD3_TEST_SRC})
target_link_libraries(SD3_Test PRIVATE SD3_Core Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(SD3_Test EXTRA_ARGS --success --durations yes)
