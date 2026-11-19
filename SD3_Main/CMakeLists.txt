file(GLOB_RECURSE SD3_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(SD3 ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(SD3 PUBLIC SD3_Core)
