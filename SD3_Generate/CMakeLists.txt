file(GLOB_RECURSE SD3_GENERATE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(SD3_Generate ${SD3_GENERATE_SRC})
target_link_libraries(SD3_Generate PUBLIC SD3_Core)
