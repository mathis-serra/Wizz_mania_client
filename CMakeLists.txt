#cmake_minimum_required(VERSION 3.15)
#project(Wizz_mania_client2)
#
#set(CMAKE_CXX_STANDARD 20)
#
#add_executable(Wizz_mania_client2 main.cpp Client_2.cpp)
#
#if (WIN32)
#    target_link_libraries(Wizz_mania_client2 ws2_32)
#endif()
#
#set(THREADS_PREFER_PTHREAD_FLAG ON)
#find_package(Threads REQUIRED)
#target_link_libraries(Wizz_mania_client2 Threads::Threads)


#cmake_minimum_required(VERSION 3.15)
#project(Wizz_mania_client2)
#
#set(CMAKE_CXX_STANDARD 20)
#set(OPENSSL_ROOT_DIR "C:/Program Files/vcpkg/installed/x64-windows")
#
#
#add_executable(Wizz_mania_client2 main.cpp Client_2.cpp)
#
#if (WIN32)
#    target_link_libraries(Wizz_mania_client2 ws2_32)
#endif()
#
#set(THREADS_PREFER_PTHREAD_FLAG ON)
#find_package(Threads REQUIRED)
#find_package(OpenSSL REQUIRED)
#
#target_link_libraries(Wizz_mania_client2 Threads::Threads OpenSSL::SSL OpenSSL::Crypto)

cmake_minimum_required(VERSION 3.15)
project(Wizz_mania_client2)

set(CMAKE_CXX_STANDARD 20)

set(OPENSSL_ROOT_DIR "C:/Program Files/vcpkg/installed/x64-windows")

set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML/lib/cmake/SFML")

add_executable(Wizz_mania_client2
        main.cpp
        logic_files/cpp_files/Network.cpp
        logic_files/cpp_files/Crypto.cpp
        logic_files/cpp_files/MessageHandler.cpp
        logic_files/cpp_files/Client.cpp
        graphic_files/cpp_files/Windows.cpp
        graphic_files/cpp_files/WindowManager.cpp
        graphic_files/cpp_files/UIManager.cpp
        graphic_files/cpp_files/Button.cpp
)

include_directories("${CMAKE_SOURCE_DIR}/SFML/include")

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
link_directories("${CMAKE_SOURCE_DIR}/SFML/lib")
target_link_libraries(Wizz_mania_client2
        sfml-system
        sfml-window
        sfml-graphics
        sfml-network
        sfml-audio
)

find_package(OpenSSL REQUIRED)
target_link_libraries(Wizz_mania_client2 OpenSSL::SSL OpenSSL::Crypto)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(Wizz_mania_client2 Threads::Threads)

if (WIN32)
    target_link_libraries(Wizz_mania_client2 ws2_32)
endif()

