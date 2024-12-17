#ifndef WINDOWS_H
#define WINDOWS_H

#include "WindowManager.h"
#include "UIManager.h"
#include "../../logic_files/hpp_files/Client.h"
#include <iostream>

class Windows {
public:
    Windows(const std::string& title, int width, int height, Client& client);
    bool isRunning() const;
    void handleEvents();
    void addReceivedMessage(const std::string& message);
    void update();
    void render();
    void triggerWizz();

private:
    WindowManager windowManager;
    UIManager uiManager;
    Client& client;
    std::string userInput;

    void handleTextInput(sf::Uint32 unicode);
};

#endif