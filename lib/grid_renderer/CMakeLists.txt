add_library(grid_renderer STATIC src/grid_renderer.cpp)
target_include_directories(grid_renderer PUBLIC include)
target_link_libraries(grid_renderer PRIVATE grid window camera)