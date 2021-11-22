cmake_minimum_required(VERSION 3.5)

project(StringMathTest LANGUAGES CXX)

set(STRING_MATH_INCLUDE_PATH ..\\..\\StringMath\\StringMath)

set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)

add_subdirectory(${STRING_MATH_INCLUDE_PATH} StringMath)

add_executable(StringMathTest
  main.cpp
)
target_link_libraries(StringMathTest Qt5::Core StringMath)

target_include_directories(StringMathTest PRIVATE ${STRING_MATH_INCLUDE_PATH})

install(FILES "${CMAKE_BINARY_DIR}/StringMath/StringMath.dll" DESTINATION ${CMAKE_BINARY_DIR})
