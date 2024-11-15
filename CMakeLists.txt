cmake_minimum_required(VERSION 3.15)

project(Wizz_mania_client2)

set(CMAKE_CXX_STANDARD 20)

# Ajouter les fichiers sources
add_executable(Wizz_mania_client2
        main.cpp
        Client_2.cpp
        WindowManager.cpp
)

# Gestion des bibliothèques réseau spécifiques au système
if (WIN32)
    target_link_libraries(Wizz_mania_client2 ws2_32)
endif()

# Configuration pour les threads (multiplateforme)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(Wizz_mania_client2 Threads::Threads)

# SFML configuration
set(SFML_DIR "SFML-2.6.2") # Chemin vers SFML
include_directories(${SFML_DIR}/include)
link_directories(${SFML_DIR}/lib)

# Assurez-vous que cette option est pertinente pour votre build (static/dynamic SFML)
# add_definitions(-DSFML_STATIC) # Décommentez si vous utilisez des bibliothèques statiques SFML

# Trouver SFML et lier les composants nécessaires
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(Wizz_mania_client2 sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
