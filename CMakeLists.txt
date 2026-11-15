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

file(GLOB_RECURSE SD3_SRC ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(SD3 ${SD3_SRC})
target_include_directories(SD3 PUBLIC include)
