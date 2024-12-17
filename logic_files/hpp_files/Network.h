#ifndef NETWORK_H
#define NETWORK_H

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <iostream>

class Network {
public:
    Network();
    ~Network();
    bool connect(const std::string& serverAddress, int port, SSL*& ssl, SOCKET& serverSocket);

private:
    SSL_CTX* InitClientCTX();
    SSL_CTX* ctx;
    WSADATA wsaData;
};

#endif