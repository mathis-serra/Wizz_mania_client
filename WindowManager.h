// WindowManager.h
#include <SFML/Graphics.hpp>
#include "Client_2.h"

class WindowManager {
public:
    explicit WindowManager(Client_2 &client);
    void wizzeffect(sf::RenderWindow &window);
    void openWindow();

private:
    sf::Font m_font;
    sf::Text m_text;

    sf::RenderWindow m_window;
    sf::Clock m_clock;
    Client_2 &m_client;
};
