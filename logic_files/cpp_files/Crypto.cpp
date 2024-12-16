#include "../hpp_files/Crypto.h"

std::string Crypto::addPadding(const std::string& input) {
    size_t paddingSize = 16 - (input.size() % 16);
    std::string padded = input;
    padded.append(paddingSize, static_cast<char>(paddingSize));
    return padded;
}

std::string Crypto::removePadding(const std::string& input) {
    char paddingSize = input.back();
    return input.substr(0, input.size() - paddingSize);
}

std::string Crypto::generateKey(const std::string& password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(password.c_str()), password.size(), hash);
    return std::string(reinterpret_cast<char*>(hash), SHA256_DIGEST_LENGTH);
}

std::string Crypto::encryptMessage(const std::string& plainText, const std::string& key) {
    unsigned char iv[16];
    if (!RAND_bytes(iv, sizeof(iv))) {
        std::cerr << "Erreur de génération de l'IV." << std::endl;
        return "";
    }

    unsigned char encrypted[1024];
    int encryptedLen = 0;

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        std::cerr << "Erreur de création du contexte EVP pour le chiffrement." << std::endl;
        return "";
    }

    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL,
                           reinterpret_cast<const unsigned char*>(key.c_str()), iv) != 1) {
        std::cerr << "Erreur d'initialisation du chiffrement AES." << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        return "";
    }
    int len;
    if (EVP_EncryptUpdate(ctx, encrypted, &len,
                          reinterpret_cast<const unsigned char*>(plainText.c_str()), plainText.size()) != 1) {
        std::cerr << "Erreur lors du chiffrement des données AES." << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        return "";
    }
    encryptedLen = len;

    if (EVP_EncryptFinal_ex(ctx, encrypted + len, &len) != 1) {
        std::cerr << "Erreur lors de la finalisation du chiffrement AES." << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        return "";
    }
    encryptedLen += len;

    EVP_CIPHER_CTX_free(ctx);

    std::string encryptedMessage(reinterpret_cast<char*>(iv), sizeof(iv));
    encryptedMessage += std::string(reinterpret_cast<char*>(encrypted), encryptedLen);

    return encryptedMessage;
}

std::string Crypto::decryptMessage(const std::string& encryptedMessage, const std::string& key) {
    if (encryptedMessage.size() <= 16) {
        std::cerr << "Message chiffré trop court pour contenir un IV." << std::endl;
        return "";
    }

    unsigned char iv[16] = {0};
    std::memcpy(iv, encryptedMessage.data(), 16);

    std::string cipherText = encryptedMessage.substr(16);

    unsigned char decrypted[1024] = {0};
    int decryptedLen = 0;

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        std::cerr << "Erreur de création du contexte EVP pour le déchiffrement." << std::endl;
        return "";
    }

    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL,
                           reinterpret_cast<const unsigned char*>(key.c_str()), iv) != 1) {
        std::cerr << "Erreur d'initialisation du déchiffrement AES." << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        return "";
    }
    int len;
    if (EVP_DecryptUpdate(ctx, decrypted, &len,
                          reinterpret_cast<const unsigned char*>(cipherText.data()), cipherText.size()) != 1) {
        std::cerr << "Erreur lors du déchiffrement des données AES." << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        return "";
    }
    decryptedLen = len;

    if (EVP_DecryptFinal_ex(ctx, decrypted + len, &len) != 1) {
        std::cerr << "Erreur lors de la finalisation du déchiffrement AES." << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        return "";
    }
    decryptedLen += len;

    EVP_CIPHER_CTX_free(ctx);

    return std::string(reinterpret_cast<char*>(decrypted), decryptedLen);
}