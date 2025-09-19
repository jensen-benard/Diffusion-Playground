cmake_minimum_required(VERSION 3.16)
project(Diffusion Playground)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
)

add_executable(app ${SOURCES})

target_include_directories(app PRIVATE src)

option(ENABLE_TESTING "Enable tests" ON)
if(ENABLE_TESTING)
    enable_testing()
    find_package(Catch2 3 REQUIRED)

    set(TEST_SOURCES
        
    )

    add_executable(test_all ${TEST_SOURCES})

    target_link_libraries(test_all PRIVATE Catch2::Catch2WithMain)

    add_test(NAME TestAll COMMAND test_all)
endif()