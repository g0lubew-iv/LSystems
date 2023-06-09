cmake_minimum_required(VERSION 3.14)

project(l_systems CXX)

# include(GNUInstallDirs)

add_executable(l_system_drawer main.cpp)

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

target_sources(l_system_drawer PRIVATE ${L_SYSTEMS_SOURCES})

target_include_directories(l_system_drawer
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        )

target_compile_features(l_system_drawer PUBLIC cxx_std_20)

set_target_properties(
        l_system_drawer PROPERTIES
        PUBLIC_HEADER "${L_SYSTEMS_PUBLIC_HEADERS}"
)

find_package(OpenGL REQUIRED)
target_link_libraries(l_system_drawer PUBLIC OpenGL::GL)

find_package(glfw3 REQUIRED)
target_link_libraries(l_system_drawer PUBLIC glfw)

find_package(glad REQUIRED)
target_link_libraries(l_system_drawer PUBLIC glad::glad)

find_package(glm REQUIRED)
target_link_libraries(l_system_drawer PUBLIC glm::glm)

find_package(Boost REQUIRED)
target_link_libraries(l_system_drawer PUBLIC Boost::boost)

add_custom_target(
        copy_shaders
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/shaders
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/shaders ${CMAKE_CURRENT_BINARY_DIR}/shaders
)

add_dependencies(l_system_drawer copy_shaders)

# add_subdirectory(tests)
