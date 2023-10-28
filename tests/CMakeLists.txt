cmake_minimum_required(VERSION 3.15)

set(target_name tests)

find_package(GTest CONFIG REQUIRED)

aux_source_directory(. tests_sources)
add_executable(${target_name} ${tests_sources})
target_link_libraries(${target_name} PRIVATE
    lib_my_widgets
    GTest::gtest GTest::gtest_main
)
install(TARGETS ${target_name} DESTINATION bin)