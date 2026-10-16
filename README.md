# Linux Performance Benchmarking Tool

## Project Overview
A C-based application that measures CPU computation,
memory allocation and initialization, and file I/O performance
on Linux systems.

## Technologies
- C programming language
- GCC compiler
- Ubuntu 24.04 on WSL2
- Git and GitHub

## Features
1. CPU calculation benchmark
2. Memory allocation and initialization benchmark
3. File writing and reading benchmark
4. Three repeated benchmark rounds
5. Average execution time calculation
6. CSV result logging
7. Interactive menu for individual or combined tests

## Compilation
gcc -std=c11 -Wall -Wextra benchmark.c -o benchmark

## Execution
./benchmark

Select option 4 to run all benchmarks.

## Sample Results
CPU average: 0.017715 seconds
Memory average: 0.002700 seconds
File I/O average: 0.007934 seconds

These are sample measurements from one run on the
development system. Results may vary.

## Output
benchmark_results.csv stores individual run measurements.

## Limitations
The current version measures selected operations rather
than complete system-wide performance.

## Future Enhancements
- System resource monitoring
- More benchmark repetitions
- Performance graphs
- Comparison across different systems
