cmake_minimum_required(VERSION 3.0)

project(Sender)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/asio-1.36.0/include",
    .
)
