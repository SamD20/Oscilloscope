cmake_minimum_required(VERSION 3.20)

project(mathMusic LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}")

file(GLOB SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")

find_package(Qt6 6.11 QUIET COMPONENTS Widgets)

if(NOT Qt6_FOUND)
    file(GLOB QT_INSTALLATIONS
        "C:/Qt/*/mingw_64"
        "C:/Qt/*/msvc*_64"
        "C:/Qt/*/msvc*"
    )

    foreach(QT_INSTALLATION IN LISTS QT_INSTALLATIONS)
        if(EXISTS "${QT_INSTALLATION}/lib/cmake/Qt6/Qt6Config.cmake")
            find_package(
                Qt6 6.11 QUIET
                COMPONENTS Widgets
                PATHS "${QT_INSTALLATION}"
                NO_DEFAULT_PATH
            )

            if(Qt6_FOUND)
                break()
            endif()
        endif()
    endforeach()
endif()

if(NOT Qt6_FOUND)
    message(FATAL_ERROR
        "Qt 6.11 or newer with Qt Widgets was not found. "
        "Install Qt and select a compatible desktop compiler kit."
    )
endif()

qt_standard_project_setup()

qt_add_executable(mathMusic ${SOURCES})

target_link_libraries(mathMusic PRIVATE Qt6::Widgets)

if(MSVC)
    target_compile_options(mathMusic PRIVATE /bigobj)
endif()