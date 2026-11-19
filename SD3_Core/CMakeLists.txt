file(GLOB_RECURSE SD3_CORE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(SD3_Core ${SD3_CORE_SRC})
target_include_directories(SD3_Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
