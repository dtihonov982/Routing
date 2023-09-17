cmake_minimum_required(VERSION 3.25)

set (ROUTER_SRCS 
          Rect.cpp
          Pin.cpp
          CellType.cpp
          Cell.cpp
          CellsLoader.cpp
          CellsAllocator.cpp
          #Wires.cpp
          Circuit.cpp
          #Router.cpp
          #CircuitBuilder.cpp
)

add_library (Router STATIC ${ROUTER_SRCS})

target_include_directories (Router PUBLIC "${PROJECT_SOURCE_DIR}/src"
                                           "${PROJECT_SOURCE_DIR}/include")
#target_compile_options (Router PUBLIC -fsanitize=address)
#target_link_options (Router PUBLIC -fsanitize=address)
