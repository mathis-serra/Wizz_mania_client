#ifndef CLIENT_2_H
#define CLIENT_2_H

#include <ws2tcpip.h>
#include <string>
#include <thread>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

class Client_2 {
public:
    Client_2(const std::string &ipAddress, int port);
    ~Client_2();
    bool connectToServer();
    // void sendMessage();
    void receiveMessage();

    void sendMessage(const std::string & string);

private:
    std::string ipAddress;
    int port;
    SOCKET clientSocket;
    WSADATA wsaData;
    std::thread receiveThread;
};

#endif
