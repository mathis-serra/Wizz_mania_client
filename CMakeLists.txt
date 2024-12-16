cmake_minimum_required(VERSION 3.15)
project(Wizz_mania_client2)

set(CMAKE_CXX_STANDARD 20)

# Find OpenSSL
find_package(OpenSSL REQUIRED)

# Find Threads (for background receiving)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# SFML (required for the UI components)
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Define the executable target
add_executable(Wizz_mania_client2
        main.cpp
        logic_files/cpp_files/Network.cpp
        logic_files/cpp_files/Crypto.cpp
        logic_files/cpp_files/MessageHandler.cpp
        logic_files/cpp_files/Client.cpp
        graphic_files/cpp_files/Windows.cpp
        graphic_files/cpp_files/UIManager.cpp
        graphic_files/cpp_files/Button.cpp
        graphic_files/cpp_files/WindowManager.cpp
)

# Link libraries to the target AFTER defining it
target_link_libraries(Wizz_mania_client2
        OpenSSL::SSL
        OpenSSL::Crypto
        Threads::Threads
        sfml-system
        sfml-window
        sfml-graphics
)
