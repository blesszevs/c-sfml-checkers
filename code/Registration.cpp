#include "Registration.h"
#include <iostream>
#include "Textbox.h"

using namespace sf;

Registration::Registration(const std::string& name, const std::string& information) :
    name(name),
    information(information),
    opponentName("Computer")
{
    if (!font.loadFromFile("ARIAL.ttf")) {
        std::cout << "Error loading font!" << std::endl;
    }

    nameText.setFont(font);
    nameText.setFillColor(sf::Color::White);
    nameText.setString(name);
    nameText.setCharacterSize(50);
    nameText.setPosition(300, 100);

    infoText.setFont(font);
    infoText.setFillColor(sf::Color::White);
    infoText.setString(information);
    infoText.setCharacterSize(25);
    infoText.setPosition(300, 150);

    promptText.setFont(font);
    promptText.setFillColor(sf::Color::White);
    promptText.setString("Enter your nickname:");
    promptText.setCharacterSize(30);
    promptText.setPosition(300, 250);


    inputField.setFillColor(sf::Color::Transparent);
    inputField.setOutlineThickness(2);
    inputField.setOutlineColor(sf::Color::White);
    inputField.setSize(sf::Vector2f(200, 40));
    inputField.setPosition(300, 300);

    inputBackground.setFillColor(sf::Color(220, 220, 220));
    inputBackground.setSize(sf::Vector2f(200, 40));
    inputBackground.setPosition(300, 300);

    textbox = new Textbox(font, sf::Vector2f(300, 300), sf::Vector2f(200, 40));
}

const std::string& Registration::getPlayerName() const {
    return playerName;
}

const std::string& Registration::getOpponentName() const {
    return opponentName;
}

void Registration::setOpponentName(const std::string& name) {
    opponentName = name;
}

void Registration::handleInput(sf::Event& event) {
    textbox->handleEvent(event);
    playerName = textbox->getText(); 
    playerNameText.setString(playerName); 
}

void Registration::displayInformation(sf::RenderWindow& window) {
    window.draw(nameText);
    window.draw(infoText);
    window.draw(promptText);
    textbox->draw(window);
    window.draw(playerNameText); 
}