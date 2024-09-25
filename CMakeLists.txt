cmake_minimum_required(VERSION 3.12)

project (Tsubasa)

set(CMAKE_CXX_STANDARD 17)
set(INTERPROCEDURAL_OPTIMIZATION TRUE)

include_directories(Tsubasa src tools)
link_directories(Tsubasa lib)

add_compile_definitions(JPH_PROFILE_ENABLED JPH_DEBUG_RENDERER JPH_CROSS_PLATFORM_DETERMINISTIC)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.h ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(Tsubasa ${SRC_FILES})
target_link_libraries(Tsubasa raylib)

set_target_properties(Tsubasa PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bundle
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bundle
                      INTERPROCEDURAL_OPTIMIZATION TRUE
)

# add_custom_command(TARGET Tsubasa 
#     POST_BUILD COMMAND 
#     ${CMAKE_INSTALL_NAME_TOOL} -add_rpath "@executable_path/../lib/"
#     $<TARGET_FILE:Tsubasa>)