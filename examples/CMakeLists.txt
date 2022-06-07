project(examples)

add_executable(examples test.cpp)
target_link_libraries(examples PUBLIC am-duong-lich)
target_link_directories(examples PUBLIC ${SOURCE_DIR}/include)