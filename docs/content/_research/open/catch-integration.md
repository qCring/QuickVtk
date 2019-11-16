---
layout: subpage
nav: research
title: Catch integration
category: open
---

## Integration of the Catch testing framework
[Catch2](https://github.com/catchorg/Catch2) integration could be worth some research. Setup looks pretty straight-forward

- Provide a separate `Test` target with a dependency to **QuickVtkCore**
- implement test cases for all relevant wrapper classes

The test target could be a simple console application which writes test results to the output stream or a file. Another option would be to use a QML application in order to also include application logic in various test scenarios where it seems reasonable.
