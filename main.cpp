#include "logic_files/hpp_files/Client.h"
#include "graphic_files/hpp_files/Windows.h"
#include <iostream>
#include <string>

int main() {
    // Client client("192.168.0.48", 42000);
    Client client("10.10.5.55", 42000);

    if (!client.connectToServer()) {
        std::cerr << "Échec de la connexion au serveur." << std::endl;
        return 1;
    }
    std::cout << "Connecté au serveur !" << std::endl;

    Windows window("Client Réseau - SFML", 800, 600, client);

    client.setMessageCallback([&window](const std::string& message) {
        window.addReceivedMessage("Mathis : " + message);
    });

    client.startReceiving();

    while (window.isRunning()) {
        window.handleEvents();
        window.update();
        window.render();
    }

    return 0;
}

