#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "graphic_files/hpp_files/Windows.h"
#include "logic_files/hpp_files/Client.h"
#include <iostream>

int main() {
    Client client("10.10.4.146", 42000);
    Windows windows("Wizz Mania Client", 800, 600, client);

    if (!client.connectToServer()) {
        std::cerr << "Connection failed!" << std::endl;
        return -1;
    }

    client.setMessageCallback([&windows](const std::string& message) {
        windows.addReceivedMessage("Walid : " + message);
    });

    client.startReceiving(); // Start receiving messages

    std::string userInput;

    while (windows.isRunning()) {
        windows.handleEvents();

        // Update UI and window
        windows.update();
        windows.render();
    }

    return 0;
}
