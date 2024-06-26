#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Textbox {
public:
    Textbox(const sf::Font& font, const sf::Vector2f& position, const sf::Vector2f& size,
        const sf::Color& textColor = sf::Color::Black,
        const sf::Color& backgroundColor = sf::Color(220, 220, 220),
        const sf::Color& outlineColor = sf::Color::Black);

    void draw(sf::RenderWindow& window) const;
    void handleEvent(sf::Event& event);
    const std::string& getText() const;

private:
    sf::Font font;
    sf::Text text;
    sf::RectangleShape background;
    sf::RectangleShape outline;

    std::string string;
    sf::Vector2f position;
    sf::Vector2f size;

    sf::Color textColor;
    sf::Color backgroundColor;
    sf::Color outlineColor;

    void updateTextPosition();
};