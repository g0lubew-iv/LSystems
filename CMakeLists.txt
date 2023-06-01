cmake_minimum_required(VERSION 3.14)

project(l_systems CXX)

add_library(l_systems STATIC)

set(L_SYSTEMS_PUBLIC_HEADERS
        include/lsystem/lsystem.hpp
        include/lsystem/drawer.hpp
        include/lsystem/renderer.hpp
        include/lsystem/reader.hpp
        )

set(L_SYSTEMS_SOURCES
        ${L_SYSTEMS_PUBLIC_HEADERS}
        src/lsystem.cpp
        src/drawer.cpp
        src/renderer.cpp
        src/reader.cpp
        )

target_sources(l_systems PRIVATE ${L_SYSTEMS_SOURCES})

target_include_directories(l_systems
        PUBLIC
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

find_package(OpenGL REQUIRED)
target_link_libraries(l_systems PUBLIC OpenGL::GL)

find_package(glfw3 REQUIRED)
target_link_libraries(l_systems PUBLIC glfw)

find_package(glad REQUIRED)
target_link_libraries(l_systems PUBLIC glad::glad)

find_package(glm REQUIRED)
target_link_libraries(l_systems PUBLIC glm::glm)

add_custom_target(
        copy_shaders
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/shaders
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/shaders ${CMAKE_CURRENT_BINARY_DIR}/shaders
        COMMENT "Copying ${CMAKE_CURRENT_SOURCE_DIR}/shaders to ${CMAKE_CURRENT_BINARY_DIR}/shaders"
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/shaders ${CMAKE_CURRENT_BINARY_DIR}/tests/shaders
        COMMENT "For tests: copying ${CMAKE_CURRENT_SOURCE_DIR}/shaders to ${CMAKE_CURRENT_BINARY_DIR}/tests/shaders"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_dependencies(l_systems copy_shaders)

add_subdirectory(tests)
