cmake_minimum_required(VERSION 3.14)

project(l_systems
        VERSION 1.0.0
        DESCRIPTION "LSystems and OpenGL"
        LANGUAGES CXX)

include(GNUInstallDirs)

add_executable(l_system_drawer main.cpp)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/bin)

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
    set(DOXYGEN_OUT ${CMAKE_INSTALL_PREFIX}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT})
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target(doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}
            COMMENT "Generate API documentation with Doxygen"
            VERBATIM
            )
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate Doxygen documentation!")
endif (DOXYGEN_FOUND)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIR})
target_link_libraries(l_system_drawer PUBLIC OpenGL::GL)

find_package(glfw3 REQUIRED)
include_directories(${glfw_INCLUDE_DIR})
target_link_libraries(l_system_drawer PUBLIC glfw)

find_package(glad REQUIRED)
include_directories(${glad_INCLUDE_DIR})
target_link_libraries(l_system_drawer PUBLIC glad::glad)

find_package(glm REQUIRED)
include_directories(${glm_INCLUDE_DIR})
target_link_libraries(l_system_drawer PUBLIC glm::glm)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(l_system_drawer PUBLIC Boost::boost)

find_package(Stb REQUIRED)
include_directories(${Stb_INCLUDE_DIR})
target_include_directories(l_system_drawer PUBLIC ${Stb_INCLUDE_DIR})

if (WIN32)
    set(OpenGL_RUNTIME_PATH "${OpenGL_DIR}/../../bin")
    set(glfw_RUNTIME_PATH "${glfw_DIR}/../../bin")
    set(glad_RUNTIME_PATH "${glad_DIR}/../../bin")
    set(glm_RUNTIME_PATH "${glm_DIR}/../../bin")
    set(Boost_RUNTIME_PATH "${Boost_DIR}/../../bin")
    set(Stb_RUNTIME_PATH "${Stb_DIR}/../../bin")
else ()
    set(OpenGL_RUNTIME_PATH "${OpenGL_DIR}/../../lib")
    set(glfw_RUNTIME_PATH "${glfw_DIR}/../../bin")
    set(glad_RUNTIME_PATH "${glad_DIR}/../../bin")
    set(glm_RUNTIME_PATH "${glm_DIR}/../../bin")
    set(Boost_RUNTIME_PATH "${Boost_DIR}/../../bin")
    set(Stb_RUNTIME_PATH "${Stb_DIR}/../../bin")
endif ()

install(DIRECTORY "${OpenGL_RUNTIME_PATH}/"
        DESTINATION ${CMAKE_INSTALL_PREFIX}
        )
install(DIRECTORY "${glfw_RUNTIME_PATH}/"
        DESTINATION ${CMAKE_INSTALL_PREFIX}
        )
install(DIRECTORY "${glad_RUNTIME_PATH}/"
        DESTINATION ${CMAKE_INSTALL_PREFIX}
        )
install(DIRECTORY "${glm_RUNTIME_PATH}/"
        DESTINATION ${CMAKE_INSTALL_PREFIX}
        )
install(DIRECTORY "${Boost_RUNTIME_PATH}/"
        DESTINATION ${CMAKE_INSTALL_PREFIX}
        )
install(DIRECTORY "${Stb_RUNTIME_PATH}/"
        DESTINATION ${CMAKE_INSTALL_PREFIX}
        )

install(
        TARGETS l_system_drawer DESTINATION ${CMAKE_INSTALL_PREFIX}
        PUBLIC_HEADER DESTINATION include
)

install(FILES test.txt DESTINATION ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY shaders DESTINATION ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY output DESTINATION ${CMAKE_INSTALL_PREFIX})
