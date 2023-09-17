#!/bin/bash
mkdir build
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release &&
cmake --build build -j 12
