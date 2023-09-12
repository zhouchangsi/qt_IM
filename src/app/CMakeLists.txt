set(TARGET_NAME app)
set(CMAKE_FIND_LIBRARY_CUSTOM_LIB_SUFFIX ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

# Inclusion of Qt5
if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED CONFIG)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

# Enable debug logging on RELWITHDEBINFO configuration
set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
    $<$<CONFIG:RELWITHDEBINFO>:QT_MESSAGELOGCONTEXT>
)

add_executable(${TARGET_NAME} ${PROJECT_SOURCES})
target_link_libraries(${TARGET_NAME} PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets)

# Copy Qt5 DLLs to the output directory
get_target_property(QT_DLL_LOCATION_Core Qt5::Core IMPORTED_LOCATION_RELEASE)
get_target_property(QT_DLL_LOCATION_Gui Qt5::Gui IMPORTED_LOCATION_RELEASE)
get_target_property(QT_DLL_LOCATION_Widgets Qt5::Widgets IMPORTED_LOCATION_RELEASE)
message(STATUS "QT_DLL_LOCATION_Core: ${QT_DLL_LOCATION_Core}")
message(STATUS "QT_DLL_LOCATION_Gui: ${QT_DLL_LOCATION_Gui}")
message(STATUS "QT_DLL_LOCATION_Widgets: ${QT_DLL_LOCATION_Widgets}")
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${QT_DLL_LOCATION_Core}
    ${QT_DLL_LOCATION_Gui}
    ${QT_DLL_LOCATION_Widgets}
    $<TARGET_FILE_DIR:${TARGET_NAME}>
)