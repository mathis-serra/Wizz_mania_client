#include "../hpp_files/Network.h"

Network::Network() {
    SSL_library_init();
    ctx = InitClientCTX();
}

Network::~Network() {
    SSL_CTX_free(ctx);
    WSACleanup();
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

bool Network::connect(const std::string& serverAddress, int port, SSL*& ssl, SOCKET& serverSocket) {
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "Erreur d'initialisation de WinSock : " << result << std::endl;
        return false;
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Erreur de création du socket : " << WSAGetLastError() << std::endl;
        return false;
    }

    sockaddr_in serverInfo;
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_port = htons(port);
    serverInfo.sin_addr.s_addr = inet_addr(serverAddress.c_str());

    if (::connect(serverSocket, (SOCKADDR*)&serverInfo, sizeof(serverInfo)) == SOCKET_ERROR) {
        std::cerr << "Échec de la connexion au serveur : " << WSAGetLastError() << std::endl;
        return false;
    }

    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, serverSocket);
    if (SSL_connect(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
        return false;
    }

    std::cout << "Connexion sécurisée établie avec le serveur." << std::endl;
    return true;
}