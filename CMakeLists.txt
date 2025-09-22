cmake_minimum_required(VERSION 3.16)
project(DiffusionPlayground)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(lib/particle)
add_subdirectory(lib/window)
add_subdirectory(lib/sdl_system)
add_subdirectory(lib/timer)

set(SOURCES
    apps/monte_carlo.cpp
    apps/main.cpp
    apps/diffusion_explicit.cpp
)

#add_compile_options(-Wall -Wextra -Wpedantic)
find_package(SDL2 REQUIRED)

add_executable(app ${SOURCES})

target_include_directories(app PRIVATE include)

target_link_libraries(
    app 
    PRIVATE 
    particle
    window
    sdl_system
    timer)

# option(ENABLE_TESTING "Enable tests" OFF)
# if(ENABLE_TESTING)
#     enable_testing()
#     find_package(Catch2 3 REQUIRED)

#     set(TEST_SOURCES
        
#     )

#     add_executable(test_all ${TEST_SOURCES})

#     target_link_libraries(test_all PRIVATE Catch2::Catch2WithMain)

#     add_test(NAME TestAll COMMAND test_all)
# endif()