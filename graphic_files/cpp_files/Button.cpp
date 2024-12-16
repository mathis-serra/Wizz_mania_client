#include "../hpp_files/Button.h"

Button::Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& text, const sf::Font& font) {
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(sf::Color(82, 102, 23));

    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(20);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(
        position.x + (size.x - buttonText.getLocalBounds().width) / 8,
        position.y + (size.y - buttonText.getLocalBounds().height) / 4

    );
}

void Button::render(sf::RenderWindow& window) const {
    window.draw(shape);
    window.draw(buttonText);
}

bool Button::isClicked(const sf::Vector2f& mousePosition) const {
    return shape.getGlobalBounds().contains(mousePosition);
}