#include "Textbox.h"
using namespace sf;
Textbox::Textbox(const sf::Font& font, const sf::Vector2f& position, const sf::Vector2f& size,
    const sf::Color& textColor, const sf::Color& backgroundColor,
    const sf::Color& outlineColor) :
    font(font),
    text("", font, 20),
    background(sf::Vector2f(size.x, size.y)),
    outline(sf::Vector2f(size.x, size.y)),
    string(""),
    position(position),
    size(size),
    textColor(textColor),
    backgroundColor(backgroundColor),
    outlineColor(outlineColor)
{
    text.setFillColor(textColor);
    text.setPosition(position);

    background.setFillColor(backgroundColor);
    background.setPosition(position);

    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineThickness(2);
    outline.setOutlineColor(outlineColor);
    outline.setPosition(position);

    updateTextPosition();
}

void Textbox::draw(sf::RenderWindow& window) const {
    window.draw(background);
    window.draw(outline);
    window.draw(text);
}

void Textbox::handleEvent(sf::Event& event) {
    if (event.type == Event::TextEntered) {
        if (event.text.unicode == '\b' && !string.empty()) {
            string.erase(string.length() - 1);
        }
        else if (event.text.unicode >= 32 && event.text.unicode <= 126) {
            string += static_cast<char>(event.text.unicode);
        }
        text.setString(string);
        updateTextPosition();
    }
}

const std::string& Textbox::getText() const {
    return string;
}

void Textbox::updateTextPosition() {
    text.setPosition(position.x + 5, position.y + 5);
}