#ifndef CLIENT_H
#define CLIENT_H

#include "Network.h"
#include "MessageHandler.h"
#include <functional>
#include <iostream>
#include <string>

class Client {
public:
    Client(const std::string& serverAddress, int port);
    ~Client();
    bool connectToServer();
    void startReceiving();
    bool sendMessage(const std::string& message);
    void setMessageCallback(std::function<void(const std::string&)> callback);

private:
    Network network;
    MessageHandler* messageHandler;
    SSL* ssl;
    SOCKET serverSocket;
    std::string serverAddress;
    int port;
    std::string sessionKey;
    std::function<void(const std::string&)> messageCallback;
};

#endif