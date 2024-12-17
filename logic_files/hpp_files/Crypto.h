#ifndef CRYPTO_H
#define CRYPTO_H

#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <iostream>
#include <cstring>
#include <string>

class Crypto {
public:
    static std::string encryptMessage(const std::string& plainText, const std::string& key);
    static std::string decryptMessage(const std::string& encryptedMessage, const std::string& key);
    static std::string generateKey(const std::string& password);
    static std::string addPadding(const std::string& input);
    static std::string removePadding(const std::string& input);
};

#endif