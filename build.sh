#!/bin/bash
test ! -d build && mkdir build

if [ $# -eq 0 ]
then
    cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
elif [ $1 = debug ] 
then 
    cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug -DUSE_ASAN=OFF
elif [ $1 = asan ] 
then 
    cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug -DUSE_ASAN=ON
else
    echo "Unrecognized option $1"
    exit 1
fi

if [ $? -eq 0 ]
then
    cmake --build build -j 12
fi
