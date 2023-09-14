set(target_name app)


# Enable debug logging on RELWITHDEBINFO configuration
set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
    $<$<CONFIG:RELWITHDEBINFO>:QT_MESSAGELOGCONTEXT>
)

# app
add_subdirectory(widgets)
add_executable(${target_name} main.cpp)
target_link_libraries(${target_name} lib_my_widgets)
install(DIRECTORY resources
    DESTINATION bin
)
# app end

install(TARGETS ${target_name} 
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

# Copy Qt5 DLLs to the output directory
# get_target_property(QT_DLL_LOCATION_Core Qt5::Core IMPORTED_LOCATION_RELEASE)
# get_target_property(QT_DLL_LOCATION_Gui Qt5::Gui IMPORTED_LOCATION_RELEASE)
# get_target_property(QT_DLL_LOCATION_Widgets Qt5::Widgets IMPORTED_LOCATION_RELEASE)
# message(STATUS "QT_DLL_LOCATION_Core: ${QT_DLL_LOCATION_Core}")
# message(STATUS "QT_DLL_LOCATION_Gui: ${QT_DLL_LOCATION_Gui}")
# message(STATUS "QT_DLL_LOCATION_Widgets: ${QT_DLL_LOCATION_Widgets}")
# add_custom_command(TARGET ${target_name} POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#     ${QT_DLL_LOCATION_Core}
#     ${QT_DLL_LOCATION_Gui}
#     ${QT_DLL_LOCATION_Widgets}
#     $<TARGET_FILE_DIR:${target_name}>
# )