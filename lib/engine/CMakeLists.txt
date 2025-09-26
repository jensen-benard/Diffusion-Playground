add_library(engine STATIC src/engine.cpp)
target_include_directories(engine PUBLIC include)
target_link_libraries(engine PRIVATE window simulation_manager grid_renderer grid camera)