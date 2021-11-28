# Introduction

The **"StringMath"** library provides calculation of mathematical expressions in string format.
Expressions can contain several mathematical operations and subexpressions in brackets.
Basic arithmetic operations, trigonometric and logarithmic functions are available for calculations.
Calculations are made with double precision. The result of calculations is given with a specified number of decimal places.

# Installation

The library works on Windows and can be built in Qt Creator or in a terminal.

**Dependencies:**
- Qt5 Core (library and test);
- Qt5 Widgets (example).
 
Build order on the command line:

```
git clone https://github.com/psivitsky/StringMath
cd StringMath
cmake ..
cmake --build .
```

The build of the test and the example is performed similarly, but separately.

# How to use it?

Include the header file "string_math.h" and create a class object.
Pass an expression string to the object and get the result of the calculation.
You can also pass the desired number of decimal places in the arguments of the class constructor.
If the object detects an error it throws an exception.
