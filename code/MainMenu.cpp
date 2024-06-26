#include "MainMenu.h"


MainMenu::MainMenu(float width, float height)
{
	if (!font.loadFromFile("Bebas-Regular.ttf")) {
		cout << "No font is here";
	}

	winnerText.setFont(font); 
	winnerText.setCharacterSize(70); 
	winnerText.setPosition(sf::Vector2f(200, 100)); 

	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(Color::White);
	mainMenu[0].setString("Play");
	mainMenu[0].setCharacterSize(70);
	mainMenu[0].setPosition(200, 200);

	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(Color::White);
	mainMenu[1].setString("Options");
	mainMenu[1].setCharacterSize(70);
	mainMenu[1].setPosition(200, 300);

	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(Color::White);
	mainMenu[2].setString("Registration");
	mainMenu[2].setCharacterSize(70);
	mainMenu[2].setPosition(200, 400);

	mainMenu[3].setFont(font);
	mainMenu[3].setFillColor(Color::White);
	mainMenu[3].setString("Exit");
	mainMenu[3].setCharacterSize(70);
	mainMenu[3].setPosition(200, 500);

	MainMenuSelected = -1;
}
MainMenu::~MainMenu()
{

}

void MainMenu::draw(RenderWindow& window) {
	for (int i = 0; i < Max_main_menu; ++i) {
		window.draw(mainMenu[i]);
	}
	window.draw(winnerText);
}

void MainMenu::setWinnerText(PieceColor winner, const string& playerName, const string& opponentName) {
	if (winner == RED) {
		winnerText.setFont(font);
		winnerText.setString(playerName + "  Wins! ");
		winnerText.setFillColor(sf::Color::Red);
	}
	else if (winner == BLUE) {
		winnerText.setFont(font);
		winnerText.setString(opponentName + "  Wins! ");
		winnerText.setFillColor(sf::Color::Blue);
	}
	else {
		winnerText.setFont(font);
		winnerText.setString("It's a Draw!");
		winnerText.setFillColor(sf::Color::White);
	}
}
int MainMenu::handleMouseClick(int mouseX, int mouseY) {
	for (int i = 0; i < Max_main_menu; ++i) {
		sf::FloatRect textBounds = mainMenu[i].getGlobalBounds();
		if (textBounds.contains(mouseX, mouseY)) {
			mainMenu[MainMenuSelected].setFillColor(Color::White); 
			MainMenuSelected = i;
			mainMenu[MainMenuSelected].setFillColor(Color::Red);
			return MainMenuSelected; 
		}
	}
	return -1; // No option was clicked
}
