cmake_minimum_required(VERSION 3.25)

set (TRACING_SRCS 
          Pin.cpp
          Rect.cpp
          CellType.cpp
)

add_library (Tracing STATIC ${TRACING_SRCS})

target_include_directories (Tracing PUBLIC "${PROJECT_SOURCE_DIR}/src"
                                           "${PROJECT_SOURCE_DIR}/include")
target_compile_options (Tracing PUBLIC -fsanitize=address)
target_link_options (Tracing PUBLIC -fsanitize=address)
