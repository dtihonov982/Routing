cmake_minimum_required (VERSION 3.25)

set (SRCS 
          Pin.cpp
          Cell.cpp
)

foreach (SRC IN LISTS SRCS)
    string (REPLACE ".cpp" "" TGT ${SRC})
    add_executable(${TGT} ${SRC})
    target_compile_options (${TGT} PUBLIC -fsanitize=address)
    target_link_options (${TGT} PUBLIC -fsanitize=address)
    target_include_directories (${TGT} PUBLIC "${PROJECT_SOURCE_DIR}/src")
endforeach ()
