cmake_minimum_required(VERSION 3.25)

set (COMMON_SRCS 
          Rect.cpp
)

add_library (Common STATIC ${COMMON_SRCS})

target_include_directories (Common PUBLIC "${PROJECT_SOURCE_DIR}/src"
                                           "${PROJECT_SOURCE_DIR}/json/include")
#target_compile_options (Router PUBLIC -fsanitize=address)
#target_link_options (Router PUBLIC -fsanitize=address)
