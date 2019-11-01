---
layout: page
nav: research
title: Include Headers
category: open
---

## Improved Header Includes
- It could be better to organize `#includes` in directories to line up with namespaces
- `#include "quick/Vtk/MyClass.hpp"` over `#include "quickVtkMyClass.hpp"`.

The current strategy is to use unique identifiers like `quickVtkMyClass` for `.hpp` and `.cpp` files. However, this needs some research first since such changes involve a certain amount of project restructuring, changing things in [CMake](https://cmake.org/), and testing on different platforms & project generators.
