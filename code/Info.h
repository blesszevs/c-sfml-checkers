#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Info {
public:
    Info();
    void draw(sf::RenderWindow& window);
private:
    sf::Text infoText;
    sf::Font font;
};