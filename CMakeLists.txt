cmake_minimum_required(VERSION 3.12)
project(student_tasks_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SRC_FILES "src/*.cpp")
add_executable(student_tasks ${SRC_FILES})
