#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

class Button {
public:
    Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& text, const sf::Font& font);

    void render(sf::RenderWindow& window) const;
    bool isClicked(const sf::Vector2f& mousePosition) const;

private:
    sf::RectangleShape shape;
    sf::Text buttonText;
};

#endif