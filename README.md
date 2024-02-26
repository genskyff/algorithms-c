# Algorithms implemented in C

## Overview
This is a repository implemented in C for various basic algorithms and data structures, intended for learning and recording. It is licensed under the GPLv3 and designed to be modular, making it easy to be imported into other code.

## Features
- Uses only the C standard library, with no third-party libraries
- Unit tests for almost every function
- Strict adherence to the C17 standard, tested and passed on MSVC, GCC, and Clang

## Usage
First, you need any C compiler. GCC is installed by default on Linux, clang is installed by default on macOS, and on Windows, you can choose to install Visual Studio to use MSVC or install MinGW64.

Additionally, you need to install Clangd, as well as the build tool XMake.

To make LSP (Language Server Protocol) work correctly, you need to execute the following command:

```shell
xmake project -k compile_commands
```

Then, you can execute the program using the following command:

```shell
xmake test
```

## Roadmap
- [ ] Sorting
  - [x] Bubble sort
  - [x] Cocktail sort
  - [ ] Heap sort
  - [x] Insertion sort
  - [x] Binary insertion sort
  - [x] Shell sort
  - [x] Merge sort (recursive version)
  - [x] Merge sort (iterative version)
  - [x] Quick sort
  - [x] Selection sort
  - [ ] Bucket sort
  - [ ] Counting sort
  - [ ] Radix sort
- [ ] Data structures
  - [x] Vector
  - [x] Linear lists
    - [x] Sequential list
    - [x] Linked list
  - [ ] Queue
    - [ ] Array queue
    - [ ] Linked queue
  - [ ] Stack
    - [x] Array stack
    - [ ] Linked stack
  - [ ] Hash table
  - [ ] Tree
  - [ ] Heap
  - [ ] Graph
- [ ] Searching
- ...
