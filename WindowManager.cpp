//
// Created by drvba on 14/11/2024.
//

// WindowManager.cpp
#include "WindowManager.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

#include "Client_2.h"

WindowManager::WindowManager(Client_2 &client)
    : m_window(sf::VideoMode(800, 600), "SFML Chat Client"), m_client(client) {
    if (!m_font.loadFromFile("../Righteous-Regular.ttf")) {
        std::cerr << "Error loading font." << std::endl;
    }
}
#include <chrono>

void wizzEffect(sf::RenderWindow& window) {
    sf::Vector2i originalPosition = window.getPosition();
    int offset = 10;


    for (int i = 0; i < 10; ++i) {
        window.setPosition(sf::Vector2i(originalPosition.x + (i % 2 == 0 ? offset : -offset), originalPosition.y));
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }


    window.setPosition(originalPosition);
}



void WindowManager::openWindow() {
    std::string userInput;
    std::vector<std::pair<std::string, bool>> messages;  // Pair: message and sent/received flag

    // UI components
    sf::RectangleShape inputBox(sf::Vector2f(680, 40));
    inputBox.setPosition(10, 550);
    inputBox.setFillColor(sf::Color(205, 210, 184));

    sf::RectangleShape sendButton(sf::Vector2f(100, 40));
    sendButton.setPosition(690, 550);
    sendButton.setFillColor(sf::Color(80, 131, 110));

    sf::Text buttonText("Send", m_font, 20);
    buttonText.setPosition(710, 560);
    buttonText.setFillColor(sf::Color::White);

    sf::Text inputText("", m_font, 20);
    inputText.setPosition(20, 560);
    inputText.setFillColor(sf::Color::White);

    std::vector<sf::Text> messageTexts;

    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_window.close();

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') {  // Handle backspace
                    if (!userInput.empty())
                        userInput.pop_back();
                } else if (event.text.unicode == '\r') {  // Handle Enter key
                    if (!userInput.empty()) {
                        m_client.sendMessage(userInput);
                        messages.push_back({userInput, true});
                        userInput.clear();
                    }
                } else if (event.text.unicode < 128) {
                    userInput += static_cast<char>(event.text.unicode);
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {  // Handle mouse click
                if (sendButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    if (!userInput.empty()) {
                        m_client.sendMessage(userInput);
                        messages.push_back({userInput, true});
                        userInput.clear();
                    }
                }
            }
        }

        // Update input text
        inputText.setString(userInput);

        // Update message texts
        messageTexts.clear();
        for (size_t i = 0; i < messages.size(); ++i) {
            sf::Text msg(messages[i].first, m_font, 20);
            msg.setFillColor(messages[i].second ? sf::Color(243, 238, 217) : sf::Color::White);
            msg.setPosition(messages[i].second ? 400 : 20, 20 + i * 30);  // Right or left
            messageTexts.push_back(msg);
        }

        // Render components
        m_window.clear(sf::Color(27, 105, 95));
        m_window.draw(inputBox);
        m_window.draw(sendButton);
        m_window.draw(buttonText);
        m_window.draw(inputText);

        for (const auto &msg : messageTexts)
            m_window.draw(msg);

        m_window.display();
    }
}


void Button(sf::RenderWindow& window) {

}



