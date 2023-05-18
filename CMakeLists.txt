cmake_minimum_required(VERSION 3.14)

project(l_systems CXX)

add_library(l_systems STATIC)

set(L_SYSTEMS_PUBLIC_HEADERS
        include/lsystem/lsystem.hpp
        )

set(L_SYSTEMS_SOURCES
        ${L_SYSTEMS_PUBLIC_HEADERS}
        src/lsystem.cpp
        )

target_sources(l_systems PRIVATE ${L_SYSTEMS_SOURCES})

target_include_directories(l_systems PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        )

target_compile_features(l_systems PUBLIC cxx_std_20)

set_target_properties(
        l_systems PROPERTIES
        PUBLIC_HEADER "${L_SYSTEMS_PUBLIC_HEADERS}"
)

add_subdirectory(tests)