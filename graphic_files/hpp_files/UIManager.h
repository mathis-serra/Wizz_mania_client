#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include "Button.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

class UIManager {
public:
    enum class MessageType {
        Received,
        Sent
    };

    UIManager(float windowWidth, float windowHeight);

    void loadFont(const std::string& fontPath);
    void handleTextEntered(sf::Uint32 unicode, std::string& userInput);
    void handleScroll(float delta);
    void addMessage(const std::string& message, MessageType type);
    void updateScroll();
    void renderUI(sf::RenderWindow& window, const std::string& userInput);

    Button& getSendButton();
    Button& getWizzButton();

private:
    struct MessageBubble {
        sf::Text text;
        sf::RectangleShape bubble;
    };

    sf::Font font;
    sf::RectangleShape inputBox;
    sf::Text inputText;
    sf::RectangleShape inputScrollbar;
    std::vector<MessageBubble> messageBubbles;

    Button sendButton;
    Button wizzButton;

    float windowWidth;
    float maxInputWidth;
    float maxInputHeight;
    float lineSpacing;
    float currentHeight;
    float scrollOffset;
};

#endif // UI_MANAGER_H