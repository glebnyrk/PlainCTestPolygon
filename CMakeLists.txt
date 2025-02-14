cmake_minimum_required(VERSION 3.31)
project(test_polygon C)

set(CMAKE_C_STANDARD 11)
file(GLOB SOURCES "*.c")  # Все файлы .c в корне
file(GLOB HEADERS "*.h")
add_executable(test_polygon src/main.c src/block.c)

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})
target_link_libraries(test_polygon ${OPENSSL_LIBRARIES})
