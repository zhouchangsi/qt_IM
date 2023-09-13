cmake_minimum_required(VERSION 3.15)
project(cpp_tempalte CXX)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)

# enable windows shared library export
if (WIN32)
  set(WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

enable_testing()
add_subdirectory(src)
add_subdirectory(tests)

# add_custom_target(copy_resources ALL
#         COMMAND ${CMAKE_COMMAND} -E copy_directory
#         ${CMAKE_SOURCE_DIR}/resources
#         ${CMAKE_SOURCE_DIR}/bin/Release/resources
#         COMMENT "Copying resources into binary directory")

# add_dependencies(app copy_resources)