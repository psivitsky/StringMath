cmake_minimum_required(VERSION 3.5)

project(StringMath LANGUAGES CXX)

set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core REQUIRED)

add_library(StringMath SHARED
    string_math_base.h
    string_math.h
    string_math.cpp
    string_math_constant.h
    string_math_constant.cpp
    string_math_function.h
    string_math_function.cpp
    expression_analyzer.h
    expression_analyzer.cpp
    op_interpreter.h
    op_interpreter.cpp
    fr_op_interpreter.h
    fr_op_interpreter.cpp
    sr_op_interpreter.h
    sr_op_interpreter.cpp
    func_interpreter.h
    func_interpreter.cpp)

target_link_libraries(StringMath PRIVATE Qt5::Core)

target_compile_definitions(StringMath PRIVATE STRINGMATH_LIBRARY)
