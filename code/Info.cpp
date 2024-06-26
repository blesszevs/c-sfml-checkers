#include "Info.h"
#include <iostream>
Info::Info() {
    if (!font.loadFromFile("Bebas-Regular.ttf")) {
        std::cout << "Error loading font!" << std::endl;
    }

    infoText.setFont(font);
    infoText.setFillColor(sf::Color::White);
    infoText.setCharacterSize(18); 

    infoText.setString("The goal of the game:\n"
        "   Capture all of your opponent's checkers or block them so they cannot move.\n"
        "Initial setup:\n"
        "   Checkers are placed on the dark squares of the board.\n"
        "   Each player starts with 12 checkers.\n"
        "   The player with the red checkers moves first.\n"
        "Moves:\n"
        "   Checkers move diagonally forward one square.\n"
        "   Capture is made by jumping over an opponent's checker to an empty square diagonally.\n"
        "   Kings (checkers that have reached the opposite end of the board) can move diagonally forward and backward.\n"
        "Forced captures:\n"
        "   If a player has the opportunity to capture an opponent's checker, they are obligated to do so.\n"
        "   If, after making a capture, the same checker can make another capture, the player must continue capturing until it is no longer possible.\n"
        "Victory:\n"
        "   A player wins when they have captured all of their opponent's checkers or blocked them so they cannot move.\n"
        "Controls:\n"
        "   Left click: Select your checker\n"
        "   Left click: Drag the checker to an empty square or make a capture.\n"
        "Settings:\n"
        "   Player name: Enter your name to personalize the game.\n"
        "   Opponent name: ('Computer').\n"
        "Additional tips:\n"
        "   Keep an eye out for captures to gain an advantage.\n"
        "   Become a king to increase your movement options.\n"
        "   Block your opponent's checkers' movement to win.\n"
        "   Have a good game!);\n");

    //Center
    sf::FloatRect textRect = infoText.getLocalBounds();
    infoText.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    infoText.setPosition(sf::Vector2f(480.0f, 360.0f)); 
}

void Info::draw(sf::RenderWindow& window) {
    window.draw(infoText);
}