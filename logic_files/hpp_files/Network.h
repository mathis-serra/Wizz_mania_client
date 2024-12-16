#ifndef NETWORK_H
#define NETWORK_H

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <iostream>

class Network {
public:
    Network();
    ~Network();
    bool connect(const std::string& serverAddress, int port, SSL*& ssl, int& serverSocket);

private:
    SSL_CTX* InitClientCTX();
    SSL_CTX* ctx;
};

#endif
