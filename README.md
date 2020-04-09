# intro-sdc-histogram-filter-cpp

Histogram filter implementation using C++ 

## Features:
* C++ 14
* `cmake` project builder
* Covered with unit tests using `Google Test` framework
* Free for clone / fork and play around

## Getting Started (MacOS / Unix)
1. Clone repository
```
$ git clone https://github.com/jurayev/intro_sdc_histogram_filter_cpp
```
2. Navigate to project directory
```
$ cd intro_sdc_histogram_filter_cpp
```
3. Build cmake project, compile source files, setup googletest libraries
```
$ mkdir cmake-build-debug
$ cd cmake-build-debug 
$ ccmake ../
$ make 
```
4. Run simulate class
```
$ src/simulate
```
5. Run histogram filter unit tests
```
$ tests/run_histogram_filter_tests
```