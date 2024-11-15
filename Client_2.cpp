#include "Client_2.h"
#include <errno.h>
#include <string.h> // for strerror

Client_2::Client_2(const std::string &ipAddress, int port)
    : ipAddress(ipAddress), port(port), clientSocket(-1) {
    // No WSAStartup needed on macOS
}

Client_2::~Client_2() {
    if (clientSocket != -1) {
        close(clientSocket);  // Using close instead of closesocket
    }
    if (receiveThread.joinable()) {
        receiveThread.join();
    }
}

bool Client_2::connectToServer() {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {  // Using -1 instead of INVALID_SOCKET
        std::cerr << "Erreur de création du socket : " << strerror(errno) << std::endl;
        return false;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    if (inet_pton(AF_INET, ipAddress.c_str(), &serverAddress.sin_addr) <= 0) {
        std::cerr << "Adresse IP invalide : " << strerror(errno) << std::endl;
        close(clientSocket);
        return false;
    }

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Échec de la connexion au serveur : " << strerror(errno) << std::endl;
        close(clientSocket);
        return false;
    }

    std::cout << "Connecté au serveur !" << std::endl;

    receiveThread = std::thread(&Client_2::receiveMessage, this);

    return true;
}

void Client_2::sendMessage() {
    std::string message;
    while (true) {
        std::cout << "Entrez un message (ou 'exit' pour quitter) : ";
        std::getline(std::cin, message);

        if (message == "exit") break;

        ssize_t sendResult = send(clientSocket, message.c_str(), message.size() + 1, 0);
        if (sendResult == -1) {  // Using -1 instead of SOCKET_ERROR
            std::cerr << "Erreur d'envoi : " << strerror(errno) << std::endl;
            break;
        }
    }
}

void Client_2::receiveMessage() {
    char buffer[1024];
    while (true) {
        ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            std::cout << "\nMessage reçu : " << buffer << "\n> ";
        } else if (bytesReceived == 0) {
            std::cout << "Connexion fermée par le serveur." << std::endl;
            break;
        } else {
            std::cerr << "Erreur de réception : " << strerror(errno) << std::endl;
            break;
        }
    }
}