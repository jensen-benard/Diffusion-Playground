cmake_minimum_required(VERSION 3.16)
project(DiffusionPlayground)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(lib/sdl_system)
add_subdirectory(lib/solver)
add_subdirectory(lib/window)
add_subdirectory(lib/timer)
add_subdirectory(lib/grid)
add_subdirectory(lib/simulation_controller)

set(SOURCES
    apps/main.cpp
)

#add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(app ${SOURCES})

target_include_directories(app PRIVATE include)

target_link_libraries(
    app 
    PRIVATE 
    sdl_system
    window
    solver
    timer
    grid
    simulation_controller)

# option(ENABLE_TES    sdl_systemTING "Enable tests" OFF)
# if(ENABLE_TESTING)
#     enable_testing()
#     find_package(Catch2 3 REQUIRED)

#     set(TEST_SOURCES
        
#     )

#     add_executable(test_all ${TEST_SOURCES})

#     target_link_libraries(test_all PRIVATE Catch2::Catch2WithMain)

#     add_test(NAME TestAll COMMAND test_all)
# endif()