cmake_minimum_required (VERSION 3.25)

set (SRCS route.cpp)
set (TGT route)

add_executable (${TGT} ${SRCS})
target_include_directories (${TGT} PUBLIC "${PROJECT_SOURCE_DIR}/src"
                                          "${PROJECT_SOURCE_DIR}/json/include")
target_link_libraries (${TGT} PRIVATE Common Circuit Router)
#target_compile_options (${TGT} PUBLIC -fsanitize=address)
#target_link_options (${TGT} PUBLIC -fsanitize=address)
