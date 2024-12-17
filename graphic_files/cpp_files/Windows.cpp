#include "../hpp_files/Windows.h"

Windows::Windows(const std::string& title, int width, int height, Client& client)
    : windowManager(title, width, height), uiManager(width, height), client(client), userInput("") {
    uiManager.loadFont("arial.ttf");
}

bool Windows::isRunning() const {
    return windowManager.isOpen();
}

void Windows::handleEvents() {
    sf::Event event;
    while (windowManager.getWindow().pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            windowManager.getWindow().close();
        } else if (event.type == sf::Event::TextEntered) {
            uiManager.handleTextEntered(event.text.unicode, userInput);
        } else if (event.type == sf::Event::MouseWheelScrolled) {
            uiManager.handleScroll(event.mouseWheelScroll.delta);
        } else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                if (uiManager.getSendButton().isClicked(mousePos) && !userInput.empty()) {
                    client.sendMessage(userInput);
                    uiManager.addMessage("Vous : " + userInput, UIManager::MessageType::Sent);
                    userInput.clear();
                }
                if (uiManager.getWizzButton().isClicked(mousePos)) {
                    client.sendMessage("/wizz");
                }
            }
        }
    }
}

void Windows::addReceivedMessage(const std::string& message) {

    if (message == "Mathis : /wizz") {
        triggerWizz();

    } else {
        uiManager.addMessage(message, UIManager::MessageType::Received);
    }
}

void Windows::handleTextInput(sf::Uint32 unicode) {
    if (unicode == '\r' && !userInput.empty()) {
        client.sendMessage(userInput);
        uiManager.addMessage("Vous : " + userInput, UIManager::MessageType::Sent);
        userInput.clear();
    } else {
        uiManager.handleTextEntered(unicode, userInput);
    }
}

void Windows::update() {
    uiManager.updateScroll();
}

void Windows::render() {
    windowManager.clear();
    uiManager.renderUI(windowManager.getWindow(), userInput);
    windowManager.display();
}

void Windows::triggerWizz() {
    sf::Vector2i originalPosition = windowManager.getWindow().getPosition();
    sf::Clock clock;
    int offset = 10;

    while (clock.getElapsedTime().asMilliseconds() < 500) {
        int phase = static_cast<int>(clock.getElapsedTime().asMilliseconds() / 50) % 2;
        sf::Vector2i newPosition = originalPosition + sf::Vector2i((phase == 0 ? offset : -offset), 0);
        windowManager.getWindow().setPosition(newPosition);
    }
    windowManager.getWindow().setPosition(originalPosition);
}