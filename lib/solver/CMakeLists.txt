add_library(solver STATIC src/discrete_random_walk_solver.cpp src/finite_difference_solver.cpp)
target_include_directories(solver PUBLIC include)

target_link_libraries(solver PRIVATE grid)