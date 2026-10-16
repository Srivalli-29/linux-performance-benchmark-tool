# Linux Performance Benchmarking Tool

## Project Overview
A C-based tool for measuring CPU, memory, and file I/O
benchmark execution times on Linux.

## Technologies
- C programming language
- GCC compiler
- Ubuntu 24.04 on WSL2
- Git

## Compilation
gcc benchmark.c -o benchmark

## Execution
./benchmark

## Features
1. CPU calculation benchmark
2. Memory allocation and initialization benchmark
3. File read/write benchmark
4. Run all benchmarks

## Testing
The application was compiled and executed successfully.
Measured results include CPU execution time, memory test
time, and file I/O time.

## Limitations
The current version measures selected operations and does
not yet provide complete system-wide resource measurements.
