cmake_minimum_required(VERSION 3.25)

set (CIRCUIT_SRCS 
          Pin.cpp
          CellType.cpp
          Cell.cpp
          Wires.cpp
          Circuit.cpp
)

add_library (Circuit STATIC ${CIRCUIT_SRCS})
target_link_libraries (Circuit PRIVATE Common)
target_include_directories (Circuit PUBLIC "${PROJECT_SOURCE_DIR}/src"
                                           "${PROJECT_SOURCE_DIR}/include")
#target_compile_options (Router PUBLIC -fsanitize=address)
#target_link_options (Router PUBLIC -fsanitize=address)
