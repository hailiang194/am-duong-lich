cmake_minimum_required(VERSION 3.1)
project(am-duong-lich VERSION 1.0.0)

option(BUILD_EXAMPLES "Build shared libs" ON)
option(BUILD_SHARED_LIBS "Build example" OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

add_library(am-duong-lich include/am-duong-lich.h src/am-duong-lich.cpp)

if(BUILD_SHARED_LIBS)
    message(STATUS "Build shared lib for extended api")
    if (WIN32)
        target_compile_definitions(am-duong-lich
                                   PRIVATE $<BUILD_INTERFACE:BUILD_LIBTYPE_SHARED>
                                   INTERFACE $<INSTALL_INTERFACE:USE_LIBTYPE_SHARED>
                                   )
    endif ()
    set_property(TARGET am-duong-lich PROPERTY POSITION_INDEPENDENT_CODE ON)
else()
    message(STATUS "Build static lib for extended api")
endif()

target_include_directories(am-duong-lich
    PUBLIC 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>

)

if(${BUILD_EXAMPLES} )
    add_subdirectory(examples)
endif()