cmake_minimum_required(VERSION 3.14)

project(l_systems CXX)

add_executable(drawer main.cpp)

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

target_sources(drawer PRIVATE ${L_SYSTEMS_SOURCES})

target_include_directories(drawer
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        )

target_compile_features(drawer PUBLIC cxx_std_20)

set_target_properties(
        drawer PROPERTIES
        PUBLIC_HEADER "${L_SYSTEMS_PUBLIC_HEADERS}"
)

find_package(OpenGL REQUIRED)
target_link_libraries(drawer PUBLIC OpenGL::GL)

find_package(glfw3 REQUIRED)
target_link_libraries(drawer PUBLIC glfw)

find_package(glad REQUIRED)
target_link_libraries(drawer PUBLIC glad::glad)

find_package(glm REQUIRED)
target_link_libraries(drawer PUBLIC glm::glm)

find_package(Boost REQUIRED)
target_link_libraries(drawer PUBLIC Boost::boost)

add_custom_target(
        copy_shaders
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/shaders
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/shaders ${CMAKE_CURRENT_BINARY_DIR}/shaders
        COMMENT "Copying ${CMAKE_CURRENT_SOURCE_DIR}/input.txt to ${CMAKE_CURRENT_BINARY_DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt
)

add_dependencies(drawer copy_shaders)

# add_subdirectory(tests)
