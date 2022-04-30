cmake_minimum_required(VERSION 3.5)

project(StringMathExample LANGUAGES CXX)

set(STRING_MATH_INCLUDE_PATH ..\\lib\\base)
set(STRING_MATH_WIDGET_INCLUDE_PATH ..\\lib\\widget)

set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_subdirectory(${STRING_MATH_WIDGET_INCLUDE_PATH} StringMathWidget)

add_executable(${PROJECT_NAME} WIN32
    main.cpp
    interface.cpp
    interface.h
    interface.ui)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets StringMath StringMathWidget)

target_include_directories(${PROJECT_NAME} PRIVATE ${STRING_MATH_INCLUDE_PATH} ${STRING_MATH_WIDGET_INCLUDE_PATH})

install(FILES "${CMAKE_BINARY_DIR}/StringMathWidget/StringMath/StringMath.dll" DESTINATION ${CMAKE_BINARY_DIR})
install(FILES "${CMAKE_BINARY_DIR}/StringMathWidget/StringMathWidget.dll" DESTINATION ${CMAKE_BINARY_DIR})
