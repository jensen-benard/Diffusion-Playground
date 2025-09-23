find_package(SDL2 REQUIRED)

add_library(window STATIC src/window.cpp)
target_include_directories(window PUBLIC include)

target_link_libraries(window PRIVATE sdl_system SDL2::SDL2 timer)