cmake_minimum_required(VERSION 3.15)

set(TARGET_NAME tests)

find_package(GTest REQUIRED)
message(STATUS "GTest_INCLUDE_DIRS: ${GTest_INCLUDE_DIRS}")

include_directories(${GTest_INCLUDE_DIRS})
add_executable(${TARGET_NAME} example.cpp)
target_link_libraries(${TARGET_NAME} PRIVATE GTest::GTest GTest::Main)