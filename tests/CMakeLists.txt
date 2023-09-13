cmake_minimum_required(VERSION 3.15)

set(target_name tests)

find_package(GTest CONFIG REQUIRED)

add_executable(${target_name} example.cpp)
target_link_libraries(${target_name} PRIVATE
    GTest::GTest GTest::Main
    lib_my_widgets
)
install(TARGETS ${target_name} DESTINATION bin)