#include "Client_2.h"


Client_2::Client_2(const std::string &ipAddress, int port) : ipAddress(ipAddress), port(port), clientSocket(INVALID_SOCKET) {
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "Erreur d'initialisation de WinSock : " << result << std::endl;
    }
}

Client_2::~Client_2() {
    closesocket(clientSocket);
    WSACleanup();
    if (receiveThread.joinable()) {
        receiveThread.join();
    }
}

bool Client_2::connectToServer() {
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Erreur de création du socket : " << WSAGetLastError() << std::endl;
        WSACleanup();
        return false;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    InetPton(AF_INET, ipAddress.c_str(), &serverAddress.sin_addr);

    int result = connect(clientSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress));
    if (result == SOCKET_ERROR) {
        std::cerr << "Échec de la connexion au serveur : " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return false;
    }

    std::cout << "Connecté au serveur !" << std::endl;

    receiveThread = std::thread(&Client_2::receiveMessage, this);

    return true;
}

void Client_2::sendMessage(const std::string& message) {
    if (message == "exit") return;

    int sendResult = send(clientSocket, message.c_str(), message.size() + 1, 0);
    if (sendResult == SOCKET_ERROR) {
        std::cerr << "Erreur d'envoi : " << WSAGetLastError() << std::endl;
    }
}


void Client_2::receiveMessage() {
    char buffer[1024];
    while (true) {
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            std::cout << "\nMessage reçu : " << buffer << "\n> ";
        } else if (bytesReceived == 0) {
            std::cout << "Connexion fermée par le serveur." << std::endl;
            break;
        } else {
            std::cerr << "Erreur de réception : " << WSAGetLastError() << std::endl;
            break;
        }
    }
}

