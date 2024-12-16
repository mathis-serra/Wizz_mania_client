#include "../hpp_files/MessageHandler.h"
#include "../hpp_files/Crypto.h"

MessageHandler::MessageHandler(SSL* ssl) : ssl(ssl), running(false) {}

void MessageHandler::startReceiving(const std::function<void(const std::string&)>& callback) {
    running = true;
    std::thread(&MessageHandler::receiveMessages, this, callback, "01234567890123456789012345678901").detach();
}

void MessageHandler::receiveMessages(const std::function<void(const std::string&)>& callback, const std::string& key) {
    char buffer[1024];
    while (running) {
        int bytesReceived = SSL_read(ssl, buffer, sizeof(buffer) - 1);
        if (bytesReceived <= 0) {
            std::cerr << "Connexion perdue avec le serveur." << std::endl;
            running = false;
            break;
        }
        buffer[bytesReceived] = '\0';
        std::string encryptedMessage(buffer);
        std::string decryptedMessage = Crypto::decryptMessage(encryptedMessage, key);
        if (decryptedMessage.empty()) {
            std::cerr << "Erreur lors du déchiffrement du message." << std::endl;
            continue;
        }
        if (callback) {
            callback(decryptedMessage);
        }
    }
}

bool MessageHandler::sendMessage(const std::string& message, const std::string& key) {
    if (message.empty()) {
        std::cerr << "Message vide non envoyé." << std::endl;
        return false;
    }
    std::string encryptedMessage = Crypto::encryptMessage(message, key);
    if (encryptedMessage.empty()) {
        std::cerr << "Erreur lors du chiffrement du message." << std::endl;
        return false;
    }
    if (SSL_write(ssl, encryptedMessage.c_str(), encryptedMessage.size()) <= 0) {
        std::cerr << "Erreur lors de l'envoi du message." << std::endl;
        return false;
    }
    return true;
}