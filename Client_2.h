#ifndef CLIENT_2_H
#define CLIENT_2_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <thread>
#include <iostream>

class Client_2 {
public:
    Client_2(const std::string &ipAddress, int port);
    ~Client_2();
    bool connectToServer();
    void receiveMessage();
    void sendMessage(const std::string &message);

private:
    std::string ipAddress;
    int port;
    int clientSocket;
    std::thread receiveThread;
};

#endif
