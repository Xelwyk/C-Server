cmake_minimum_required(VERSION 3.1...3.29)
project(c-server)
include_directories(/usr/local/include)

add_executable(C-Server main.c)
target_link_libraries(C-Server PRIVATE microhttpd)
