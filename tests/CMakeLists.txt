cmake_minimum_required (VERSION 3.25)

set (SRCS 
          #[[
          PinTest.cpp
          PinLoad.cpp
          CellTypeTest.cpp
          CellsLoaderTest.cpp
          CellsAllocatorTest.cpp
          RouterTest.cpp
          ]]#
)

foreach (SRC IN LISTS SRCS)
    string (REPLACE ".cpp" "" TGT ${SRC})
    add_executable(${TGT} ${SRC})
    target_include_directories (${TGT} PUBLIC "${PROJECT_SOURCE_DIR}/src"
                                              "${PROJECT_SOURCE_DIR}/include")
    target_link_libraries (${TGT} PRIVATE Router)
    target_compile_options (${TGT} PUBLIC -fsanitize=address)
    target_link_options (${TGT} PUBLIC -fsanitize=address)
endforeach ()
