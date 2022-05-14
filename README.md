# Introduction

The **"StringMath"** library provides calculation of mathematical expressions in string format.
Expressions can contain several mathematical operations and subexpressions in brackets.
Basic arithmetic operations, trigonometric and logarithmic functions are available for calculations.
Calculations are made with double precision.

The library also contains Qt-based widget:

<p align="center">
 <img width="500" height="100" src="https://user-images.githubusercontent.com/92302433/168427893-24c5fc12-bcae-4d00-b137-09f91de985e0.png">
</p>

<p align="center">
 <img width="500" height="100" src="https://user-images.githubusercontent.com/92302433/168427943-6b25284c-bf33-4ae1-83d6-6f3288782310.png">
</p>

# Installation

The library works on Windows and can be built in Qt Creator or in a terminal.

**Dependencies:**
- Qt5 Core (base library and test);
- Qt5 Widgets (widget library abd example).
 
The order of building the base library on the command line:

```
git clone https://github.com/psivitsky/StringMath
cd StringMath\lib\base
mkdir build
cd build
cmake ..
cmake --build .
```

Build of the widget library, test and example is performed similarly, but separately (in case of the test or the example, don't forget to enter ```cmake --install .``` command).

# How to use it?

Include the header file ```string_math.h``` and create a class object.
Pass an expression string to the object and get the result of the calculation.
If the object detects an error, it throws an exception.
