# Inclusion of Qt5
if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

set(library_name lib_my_widgets)
file(GLOB_RECURSE library_sources   CONFIGURE_DEPENDS *.cpp)
file(GLOB_RECURSE library_headers   CONFIGURE_DEPENDS *.h)
file(GLOB_RECURSE library_ui_files  CONFIGURE_DEPENDS *.ui)
file(GLOB_RECURSE library_qrc_files CONFIGURE_DEPENDS *.qrc)
# exclude *_test.cpp from library_sources
list(FILTER library_sources EXCLUDE REGEX ".*_test.cpp$")

add_library(${library_name} STATIC 
    ${library_sources}
    ${library_headers} 
    ${library_ui_files}
    ${library_qrc_files}
)

find_package(Qt5 COMPONENTS Core Gui Widgets Network REQUIRED CONFIG)
target_include_directories(${library_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${library_name} PUBLIC Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network)
install(TARGETS ${library_name} DESTINATION lib)