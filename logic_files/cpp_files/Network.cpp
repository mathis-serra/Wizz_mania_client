#include "../hpp_files/Network.h"

Network::Network() {
    SSL_library_init();
    ctx = InitClientCTX();
}

Network::~Network() {
    SSL_CTX_free(ctx);
}

SSL_CTX* Network::InitClientCTX() {
    SSL_CTX* ctx;
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    ctx = SSL_CTX_new(TLS_client_method());
    if (ctx == nullptr) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    return ctx;
}

bool Network::connect(const std::string& serverAddress, int port, SSL*& ssl, int& serverSocket) {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Error creating socket: " << strerror(errno) << std::endl;
        return false;
    }

    sockaddr_in serverInfo;
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_port = htons(port);

    if (inet_pton(AF_INET, serverAddress.c_str(), &serverInfo.sin_addr) <= 0) {
        std::cerr << "Invalid address or address not supported." << std::endl;
        close(serverSocket);
        return false;
    }

    if (::connect(serverSocket, (struct sockaddr*)&serverInfo, sizeof(serverInfo)) < 0) {
        std::cerr << "Connection to the server failed: " << strerror(errno) << std::endl;
        close(serverSocket);
        return false;
    }

    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, serverSocket);
    if (SSL_connect(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
        close(serverSocket);
        return false;
    }

    std::cout << "Secure connection established with the server." << std::endl;
    return true;
}
