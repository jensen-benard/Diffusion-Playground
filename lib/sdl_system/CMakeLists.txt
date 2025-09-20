find_package(SDL2 REQUIRED)

add_library(sdl_system STATIC src/sdl_system.cpp)
target_include_directories(sdl_system PUBLIC include)

target_link_libraries(sdl_system PRIVATE SDL2::SDL2)