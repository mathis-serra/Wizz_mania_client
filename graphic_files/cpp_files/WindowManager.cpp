#include "../hpp_files/WindowManager.h"

WindowManager::WindowManager(const std::string& title, int width, int height)
    : window(sf::VideoMode(width, height), title.empty() ? "Default Window Title" : title) {}

WindowManager::~WindowManager() {}

bool WindowManager::isOpen() const {
    return window.isOpen();
}

void WindowManager::pollEvents(sf::Event& event) {
    window.pollEvent(event);
}

void WindowManager::clear() {
    window.clear();
}

void WindowManager::display() {
    window.display();
}

sf::RenderWindow& WindowManager::getWindow() {
    return window;
}
