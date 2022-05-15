cmake_minimum_required(VERSION 3.5)

project(StringMathWidget LANGUAGES CXX)

set(STRING_MATH_INCLUDE_PATH ..\\base)

set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_subdirectory(${STRING_MATH_INCLUDE_PATH} StringMath)

add_library(${PROJECT_NAME} SHARED
    string_math_widget.h
    string_math_widget.cpp
    string_math_widget.ui
    string_math_menu.h
    string_math_menu.cpp
    resources.qrc)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets StringMath)

target_include_directories(${PROJECT_NAME} PRIVATE ${STRING_MATH_INCLUDE_PATH})

target_compile_definitions(${PROJECT_NAME} PRIVATE STRINGMATHWIDGET_LIBRARY)
