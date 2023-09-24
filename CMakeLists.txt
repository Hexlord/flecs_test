cmake_minimum_required(VERSION 3.8)
cmake_policy(SET CMP0026 OLD)
project(flecs_test CXX)
find_package(Threads REQUIRED)

add_compile_definitions(
    ECS_HI_COMPONENT_ID=512
)

set(CMAKE_C_FLAGS "-Wno-enum-constexpr-conversion")
set(CMAKE_CXX_FLAGS "-Wno-enum-constexpr-conversion")

add_subdirectory(flecs)

add_executable( SECore main.cpp)
target_include_directories( SECore PUBLIC flecs/include )
target_link_libraries (SECore PUBLIC flecs_static Threads::Threads
)


set_target_properties(flecs PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
