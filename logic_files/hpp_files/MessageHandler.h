#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <string>
#include <functional>
#include <iostream>
#include <thread>
#include <openssl/ssl.h>

class MessageHandler {
public:
    MessageHandler(SSL* ssl);
    void startReceiving(const std::function<void(const std::string&)>& callback);
    bool sendMessage(const std::string& message, const std::string& key);

private:
    SSL* ssl;
    bool running;
    void receiveMessages(const std::function<void(const std::string&)>& callback, const std::string& key);
};

#endif