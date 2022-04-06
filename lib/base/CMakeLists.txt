cmake_minimum_required(VERSION 3.5)

project(StringMath LANGUAGES CXX)

set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core REQUIRED)

add_library(${PROJECT_NAME} SHARED
    string_math_base.h
    string_math_base.cpp
    string_math.h
    string_math.cpp
    string_math_constant.h
    string_math_constant.cpp
    string_math_function.h
    string_math_function.cpp    
    expression_symbol.h
    expression_symbol.cpp
    expression_operand.h
    expression_operand.cpp
    expression_operator.h
    expression_operator.cpp
    expression.h
    expression.cpp
    math_parser.h
    math_parser.cpp
    math_processor.h
    math_processor.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core)

target_compile_definitions(${PROJECT_NAME} PRIVATE STRINGMATH_LIBRARY)
