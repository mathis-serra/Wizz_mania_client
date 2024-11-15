cmake_minimum_required(VERSION 3.15)


project(Wizz_mania_client2)

set(CMAKE_CXX_STANDARD 20)

# Ajouter les fichiers sources
add_executable(Wizz_mania_client2 main.cpp
        Client_2.cpp
        WindowManager.cpp
)

# Lien avec la bibliothèque réseau sur Windows
target_link_libraries(Wizz_mania_client2 ws2_32)

# Configuration pour les threads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)


# Point the SFML_DIR to your local copy of the framework
set(SFML_DIR "SFML-2.6.2")
include_directories(${SFML_DIR}/include)
link_directories(${SFML_DIR}/lib)
add_definitions(-DSFML_STATIC)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

target_link_libraries(Wizz_mania_client2 Threads::Threads )


# Lier SFML à votre projet
target_link_libraries(Wizz_mania_client2 sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
