cmake_minimum_required(VERSION 3.14)

project(
        l_systems
        VERSION 1.0.0
        DESCRIPTION "LSystems and OpenGL"
        LANGUAGES CXX
)

include(GNUInstallDirs)

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

target_include_directories(
        l_system_drawer
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
        PRIVATE
        "${CMAKE_SOURCE_DIR}/src"
)

target_compile_features(l_system_drawer PUBLIC cxx_std_20)

set_target_properties(
        l_system_drawer PROPERTIES
        PUBLIC_HEADER "${L_SYSTEMS_PUBLIC_HEADERS}"
)

if (WIN32)
    add_custom_target(
            copy_shaders_make_dirs
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/shaders
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shaders ${CMAKE_BINARY_DIR}/shaders
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/screenshots
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/test.txt ${CMAKE_BINARY_DIR}/test.txt
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/Release/shaders
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shaders ${CMAKE_BINARY_DIR}/Release/shaders
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/Release/screenshots
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/test.txt ${CMAKE_BINARY_DIR}/Release/test.txt
    )
else ()
    add_custom_target(
            copy_shaders_make_dirs
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/shaders
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shaders ${CMAKE_BINARY_DIR}/shaders
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/screenshots
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/test.txt ${CMAKE_BINARY_DIR}/test.txt
    )
endif ()

add_dependencies(l_system_drawer copy_shaders_make_dirs)

find_package(Doxygen REQUIRED dot)
if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/docs/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT})
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target(doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Generate API documentation with Doxygen"
            VERBATIM
            )
    install(DIRECTORY ${CMAKE_BINARY_DIR}/l_systems_docs DESTINATION ${CMAKE_INSTALL_PREFIX})
else (DOXYGEN_FOUND)
    message("Doxygen wasn't found!")
endif (DOXYGEN_FOUND)

find_package(OpenGL REQUIRED)
target_link_libraries(l_system_drawer PUBLIC OpenGL::GL)

find_package(glad REQUIRED)
target_link_libraries(l_system_drawer PUBLIC glad::glad)

find_package(glfw3 REQUIRED)
target_link_libraries(l_system_drawer PUBLIC glfw)

find_package(glm REQUIRED)
target_link_libraries(l_system_drawer PUBLIC glm::glm)

find_package(Boost REQUIRED)
target_link_libraries(l_system_drawer PUBLIC Boost::boost)

find_package(Stb REQUIRED)
target_include_directories(l_system_drawer PUBLIC ${Stb_INCLUDE_DIR})

if (WIN32)
    install(
            TARGETS l_system_drawer
            RUNTIME_DEPENDENCIES
            PRE_EXCLUDE_REGEXES
            "api-ms-" "ext-ms-"
            POST_EXCLUDE_REGEXES
            ".*system32/.*\\.dll"
            DESTINATION ${CMAKE_INSTALL_PREFIX}
    )
else ()
    install(
            TARGETS l_system_drawer
            DESTINATION ${CMAKE_INSTALL_PREFIX}
    )
endif ()

install(FILES test.txt DESTINATION ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY shaders DESTINATION ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY screenshots DESTINATION ${CMAKE_INSTALL_PREFIX})
