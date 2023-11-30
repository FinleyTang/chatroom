cmake_minimum_required(VERSION 3.0)
project(MyProject)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加可执行文件 server
add_executable(server server.cpp)
target_link_libraries(server pthread)

# 添加可执行文件 client
add_executable(client client.cpp)
target_link_libraries(client pthread)