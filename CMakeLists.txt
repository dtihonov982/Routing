cmake_minimum_required(VERSION 3.25)
project(PathRounting)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

#add_subdirectory(programs)
add_subdirectory(src)
#add_subdirectory(tests)
