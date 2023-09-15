#!/bin/bash
mkdir build
cmake -B build -S . &&
cmake --build build
