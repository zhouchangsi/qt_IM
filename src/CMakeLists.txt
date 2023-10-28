set(target_name app)


# Enable debug logging on RELWITHDEBINFO configuration
set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
    $<$<CONFIG:RELWITHDEBINFO>:QT_MESSAGELOGCONTEXT>
)

# add_subdirectory(socks5)
add_subdirectory(widgets)
# app
add_executable(${target_name} main.cpp)
target_link_libraries(${target_name} lib_my_widgets)
install(DIRECTORY resources
    DESTINATION bin
)

find_package(Boost REQUIRED COMPONENTS asio)
target_link_libraries(${target_name} PRIVATE Boost::boost Boost::asio)

# app end

install(TARGETS ${target_name} 
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
