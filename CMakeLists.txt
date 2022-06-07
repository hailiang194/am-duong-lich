cmake_minimum_required(VERSION 3.1)
project(am-duong-lich VERSION 1.0.0)

set(BUILD_EXAMPLES ON)

add_library(am-duong-lich STATIC include/am-duong-lich.h src/am-duong-lich.cpp)
target_include_directories (am-duong-lich PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(${BUILD_EXAMPLES} )
    add_subdirectory(examples)
endif()