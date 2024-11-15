//
// Created by drvba on 14/11/2024.
//

// WindowManager.cpp
#include "WindowManager.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include "Client_2.h"

WindowManager::WindowManager(Client_2 &client)
    : m_window(sf::VideoMode(800, 600), "SFML window"), m_client(client) {
    if (!m_font.loadFromFile("../Righteous-Regular.ttf")) {
        std::cerr << "Erreur de chargement de la police." << std::endl;
    }
    m_text.setFont(m_font);
    m_text.setFillColor(sf::Color::White);
    m_text.setCharacterSize(50);
    m_text.setPosition(100, 100);
}

#include <chrono>

void wizzEffect(sf::RenderWindow& window) {
    sf::Vector2i originalPosition = window.getPosition();  // origin of th window
    int offset = 10;  // offset value

    // Vibration for the window
    for (int i = 0; i < 10; ++i) {
        window.setPosition(sf::Vector2i(originalPosition.x + (i % 2 == 0 ? offset : -offset), originalPosition.y));
        std::this_thread::sleep_for(std::chrono::milliseconds(50));  // pause for effect
    }

    // Restore original position
    window.setPosition(originalPosition);
}



void WindowManager::openWindow() {
    std::string userInput;
    wizzEffect(m_window);

    while (m_window.isOpen()) {
        sf::Event event{};
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_window.close();
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\r') {
                    if (!userInput.empty()) {
                        m_client.sendMessage(userInput);
                        userInput.clear();
                    }
                }
                else if (event.text.unicode < 128) {
                    userInput += static_cast<char>(event.text.unicode);
                }
            }
        }

        if (m_clock.getElapsedTime().asSeconds() >= 50) {
            m_window.close();
        }

        m_text.setString(userInput);

        m_window.clear(sf::Color::Black);
        m_window.draw(m_text);
        m_window.display();

    }
}



