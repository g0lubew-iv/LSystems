cmake_minimum_required(VERSION 3.14)

project(l_systems
        VERSION 1.0.0
        DESCRIPTION "LSystems and OpenGL"
        LANGUAGES CXX)

add_executable(l_system_drawer main.cpp)

set(L_SYSTEMS_PUBLIC_HEADERS
        include/l_system/l_system.hpp
        include/l_system/drawer.hpp
        include/l_system/renderer.hpp
        include/l_system/reader.hpp
        )

set(L_SYSTEMS_SOURCES
        ${L_SYSTEMS_PUBLIC_HEADERS}
        src/l_system.cpp
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

find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT})
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target(doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generate API documentation with Doxygen"
            VERBATIM
            )
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin
            )
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate Doxygen documentation!")
endif (DOXYGEN_FOUND)

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

install(TARGETS l_system_drawer DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)
install(DIRECTORY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)
