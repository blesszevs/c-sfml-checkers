#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Textbox.h" // Include Textbox.h here

class Registration {
public:
    Registration(const std::string& name, const std::string& information);
    void displayInformation(sf::RenderWindow& window);
    const std::string& getPlayerName() const;
    void handleInput(sf::Event& event);
    const std::string& getOpponentName() const; 
    void setOpponentName(const std::string& name); 
    std::string name;
    std::string information;
    sf::Font font;
    sf::Text nameText;
    sf::Text infoText;
    sf::Text promptText;
    sf::Text playerNameText; 
    sf::RectangleShape inputField;
    sf::RectangleShape inputBackground; 
    std::string playerName;
    std::string opponentName; 
    Textbox* textbox; 
};