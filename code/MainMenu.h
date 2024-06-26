#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Checkers.h"
#define Max_main_menu 4
#define Max_options_menu 1



using namespace std;
using namespace sf;


class MainMenu {
public:
	MainMenu(float width, float height);
	int handleMouseClick(int mouseX, int mouseY);
	void draw(RenderWindow& window);
	int MainMenuPressed();
	void setWinnerText(PieceColor winner, const string& playerName, const string& opponentName);
	~MainMenu();
private:
	int MainMenuSelected;
	Font font;
	Text mainMenu[Max_main_menu];
	sf::Text winnerText;

}; 
