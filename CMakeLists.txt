cmake_minimum_required(VERSION 3.21)
project(hw7proj)

add_executable(hw7 src/main.cpp src/parser.cpp)

target_include_directories(hw7 PRIVATE includes)
target_link_directories(hw7 PRIVATE lib)
target_link_libraries(hw7 PRIVATE rjsjai.a)
set_target_properties(
    hw7
    PROPERTIES  CXX_STANDARD          17
                CXX_STANDARD_REQUIRED ON
                RUNTIME_OUTPUT_DIRECTORY bin)
if(MSVC)
    target_compile_options(hw7 PRIVATE /MT) 
endif()
if(MINGW)
target_link_libraries(hw7 PRIVATE ws2_32)
endif()

