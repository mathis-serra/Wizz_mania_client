#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "../../SFML/include/SFML/Graphics.hpp"
#include <string>

class WindowManager {
public:
    WindowManager(const std::string& title, int width, int height);
    ~WindowManager();

    bool isOpen() const;
    void pollEvents(sf::Event& event);
    void clear();
    void display();

    sf::RenderWindow& getWindow();

private:
    sf::RenderWindow window;
};

#endif