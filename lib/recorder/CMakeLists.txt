add_library(recorder STATIC src/recorder.cpp)
target_include_directories(recorder PUBLIC include)
target_link_libraries(recorder PRIVATE file)