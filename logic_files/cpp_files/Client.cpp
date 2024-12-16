#include "../hpp_files/Client.h"
#include <unistd.h>  // For close()

Client::Client(const std::string& serverAddress, int port)
    : serverAddress(serverAddress), port(port), ssl(nullptr), serverSocket(-1), messageHandler(nullptr) {
    sessionKey = "01234567890123456789012345678901";
}

Client::~Client() {
    delete messageHandler;
    if (serverSocket != -1) {
        close(serverSocket);  // Use close() for POSIX socket cleanup
    }
}

bool Client::connectToServer() {
    if (!network.connect(serverAddress, port, ssl, serverSocket)) {
        return false;
    }
    messageHandler = new MessageHandler(ssl);
    return true;
}

void Client::startReceiving() {
    if (messageHandler) {
        messageHandler->startReceiving(messageCallback);
    }
}

bool Client::sendMessage(const std::string& message) {
    if (messageHandler) {
        return messageHandler->sendMessage(message, sessionKey);
    }
    return false;
}

void Client::setMessageCallback(std::function<void(const std::string&)> callback) {
    messageCallback = std::move(callback);
}
