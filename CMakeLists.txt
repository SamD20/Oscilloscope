cmake_minimum_required(VERSION 3.21)

project(mathMusic VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}")

file(GLOB SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")

find_package(Qt6 6.12 QUIET COMPONENTS Widgets Charts)

if(NOT Qt6_FOUND AND WIN32)
    file(GLOB QT_INSTALLATIONS "C:/Qt/6.12.*/msvc2022_64")

    foreach(QT_INSTALLATION IN LISTS QT_INSTALLATIONS)
        if(EXISTS "${QT_INSTALLATION}/lib/cmake/Qt6/Qt6Config.cmake")
            list(PREPEND CMAKE_PREFIX_PATH "${QT_INSTALLATION}")
            break()
        endif()
    endforeach()

    find_package(Qt6 6.12 REQUIRED COMPONENTS Widgets Charts)
elseif(NOT Qt6_FOUND)
    find_package(Qt6 6.12 REQUIRED COMPONENTS Widgets Charts)
endif()

qt_standard_project_setup()

qt_add_executable(mathMusic ${SOURCES})

target_link_libraries(mathMusic PRIVATE
    Qt6::Widgets
    Qt6::Charts
)

if(MSVC)
    target_compile_options(mathMusic PRIVATE /Zc:__cplusplus /bigobj)
endif()