cmake_minimum_required(VERSION 3.15)
project(Wizz_mania_client2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Wizz_mania_client2 main.cpp Client_2.cpp)

if (WIN32)
    target_link_libraries(Wizz_mania_client2 ws2_32)
endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(Wizz_mania_client2 Threads::Threads)