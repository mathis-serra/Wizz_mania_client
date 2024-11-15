#include "Client_2.h"
#include "WindowManager.h"
#include <iostream>



int main() {
    Client_2 client("10.10.140.255", 42000);
    std::cerr << "Tentative de connexion au serveur avec Client_2..." << std::endl;


    if (client.connectToServer()) {
        std::cerr << "Connecte au serveur avec succes via Client_2." << std::endl;

        std::thread sendMessageThread([&client]() {
            client.sendMessage("");
        });

        WindowManager windowManager(client);
        windowManager.openWindow();


        if (sendMessageThread.joinable()) {
            sendMessageThread.join();
        }

    } else {
        std::cerr << "Impossible de se connecter au serveur avec Client_2." << std::endl;
    }
    return 0;
}
