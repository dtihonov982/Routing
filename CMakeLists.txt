cmake_minimum_required(VERSION 3.25)
project(PathRounting)

option (USE_ASAN "Enable an address sanitizer" OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")

if (USE_ASAN)
    set(CMAKE_CXX_FLAGS_DEBUG "-g -fsanitize=address")
else ()
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
endif ()

set(CMAKE_CXX_FLAGS_RELEASE "-O2")


add_subdirectory(programs)
add_subdirectory(src)
#add_subdirectory(tests)
