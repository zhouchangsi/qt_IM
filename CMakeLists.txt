cmake_minimum_required(VERSION 3.15)
project(cpp_tempalte)

set(CMAKE_FIND_LIBRARY_CUSTOM_LIB_SUFFIX ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)

# enable windows shared library export
if (WIN32)
  set(WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)