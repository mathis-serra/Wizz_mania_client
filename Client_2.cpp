#include "Client_2.h"
#include <cerrno>
#include <cstring>

Client_2::Client_2(const std::string &ipAddress, int port)
    : ipAddress(ipAddress), port(port), clientSocket(-1) {}

Client_2::~Client_2() {
    if (clientSocket != -1) {
        close(clientSocket);
    }
    if (receiveThread.joinable()) {
        receiveThread.join();
    }
}

bool Client_2::connectToServer() {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Erreur : impossible de créer le socket" << std::endl;
        return false;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);

    if (inet_pton(AF_INET, ipAddress.c_str(), &serverAddress.sin_addr) <= 0) {
        std::cerr << "Erreur : adresse IP invalide" << std::endl;
        close(clientSocket); // Fermer le socket si inutilisable
        return false;
    }

    if (connect(clientSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Erreur : impossible de se connecter au serveur" << std::endl;
        close(clientSocket); // Fermer le socket si inutilisable
        return false;
    }

    std::cout << "Connexion établie avec le serveur" << std::endl;

    // Démarrer un thread pour recevoir des messages
    receiveThread = std::thread(&Client_2::receiveMessage, this);

    return true;
}


void Client_2::receiveMessage() {
    char buffer[1024];
    while (true) {
        ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            std::cout << "Message reçu : " << buffer << std::endl;
        } else if (bytesReceived == 0) {
            std::cout << "Le serveur a fermé la connexion" << std::endl;
            break;
        } else {
            std::cerr << "Erreur lors de la réception du message : " << strerror(errno) << std::endl;
            break;
        }
        if (clientSocket == -1) {
            std::cerr << "Socket invalide. Impossible de recevoir des messages." << std::endl;
            return;
        }
    }
}

void Client_2::sendMessage(const std::string &message) {
    ssize_t bytesSent = send(clientSocket, message.c_str(), message.length(), 0);
    if (bytesSent == -1) {
        std::cerr << "Erreur lors de l'envoi du message" << std::endl;
    } else {
        std::cout << "Message envoyé : " << message << std::endl;
    }
}
