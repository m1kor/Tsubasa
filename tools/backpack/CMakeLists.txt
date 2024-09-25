cmake_minimum_required(VERSION 3.12)

project (backpack)

set(CMAKE_CXX_STANDARD 17)

include_directories(backpack src)
include_directories(backpack ../../src)
include_directories(backpack ../../tools)

link_directories(backpack ../../lib)

file(GLOB SRC_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB SRC_UTILITIES_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/../../src/Tsubasa/*.cpp)

add_executable(backpack ${SRC_FILES} ${SRC_UTILITIES_FILES})
target_link_libraries(backpack lz4_static)

target_link_options(backpack PRIVATE /machine:x64)