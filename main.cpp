#include "Client_2.h"

int main() {
    Client_2 client("10.10.140.255",  40000);

    if (client.connectToServer()) {
        client.sendMessage();
    } else {
        std::cerr << "Impossible de se connecter au serveur." << std::endl;
    }

    return 0;
}