#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "Registration.h"
#include "Info.h"
#include "Checkers.h"
#include "Textbox.h"

using namespace sf; 

int WinMain() {
    Font font;
    if (!font.loadFromFile("ARIAL.ttf")) {
        cout << "No font is here";
    }
    RenderWindow MENU(VideoMode(960, 720), "Checkers Menu", Style::Titlebar | Style::Close);
    MainMenu mainMenu(MENU.getSize().x, MENU.getSize().y);
    Info info;

    //background
    RectangleShape background;
    background.setSize(Vector2f(960, 720));
    Texture Maintexture;
    Maintexture.loadFromFile("checkers.jpg");
    background.setTexture(&Maintexture);

    RectangleShape Pbackground;
    Pbackground.setSize(Vector2f(960, 720));
    Texture back_texture;
    back_texture.loadFromFile("Einstein.jpg");
    Pbackground.setTexture(&back_texture);

    
    bool registrationComplete = false;
    string playerName = "";

    
    Registration registration("Prybluda Yehor  KA-34", "Student of KPI IASA & The author of this program");

    while (MENU.isOpen()) {
        Event event;
        while (MENU.pollEvent(event)) {
            if (event.type == Event::Closed) {
                MENU.close();
            }

            // Handle mouse clicks for menu navigation:
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    int menuSelection = mainMenu.handleMouseClick(event.mouseButton.x, event.mouseButton.y);

                    if (menuSelection != -1) {
                        RenderWindow Play(VideoMode(960, 720), "Checkers", Style::Titlebar | Style::Close);
                        RenderWindow OPTIONS(VideoMode(960, 720), "How to play?", Style::Titlebar | Style::Close);
                        RenderWindow RegistrationWindow(VideoMode(960, 720), "Registration", Style::Titlebar | Style::Close);

                        if (menuSelection == 0 && registrationComplete) {
                            Checkers game;
                            game.playerName = registration.getPlayerName(); 
                            game.opponentName = registration.getOpponentName(); 
                            while (Play.isOpen()) {
                                Event aevent;
                                while (Play.pollEvent(aevent)) {
                                    if (aevent.type == Event::Closed) {
                                        Play.close();
                                    }
                                    if (aevent.type == Event::KeyPressed) {
                                        if (aevent.key.code == Keyboard::Escape) {
                                            Play.close();
                                        }
                                    }
                                    else if (aevent.type == Event::MouseButtonPressed) {
                                        if (aevent.mouseButton.button == sf::Mouse::Left) {
                                            game.handleMouseClick(aevent.mouseButton.x, aevent.mouseButton.y);
                                        }
                                    }
                                    if (game.checkWinCondition()) {
                                        mainMenu.setWinnerText(game.winner, registration.getPlayerName(), registration.getOpponentName());
                                        Play.close();
                                    }

                                }
                                OPTIONS.close();
                                RegistrationWindow.close();
                                Play.clear();
                                Play.draw(Pbackground);
                                game.draw(Play);
                                Play.display();
                            }
                        }
                        else if (menuSelection == 1) {
                            while (OPTIONS.isOpen()) {
                                Event aevent;
                                while (OPTIONS.pollEvent(aevent)) {
                                    if (aevent.type == Event::Closed) {
                                        OPTIONS.close();
                                    }
                                    if (aevent.type == Event::KeyPressed) {
                                        if (aevent.key.code == Keyboard::Escape) {
                                            OPTIONS.close();
                                        }
                                    }
                                }
                                Play.close();
                                RegistrationWindow.close();
                                OPTIONS.clear();
                                info.draw(OPTIONS);
                                OPTIONS.display();
                            }
                        }
                        else if (menuSelection == 2) {
                            while (RegistrationWindow.isOpen()) {
                                Event aevent;
                                while (RegistrationWindow.pollEvent(aevent)) {
                                    if (aevent.type == Event::Closed) {
                                        RegistrationWindow.close();
                                    }
                                    if (aevent.type == Event::KeyPressed) {
                                        if (aevent.key.code == Keyboard::Escape) {
                                            RegistrationWindow.close();
                                        }
                                        else if (aevent.key.code == Keyboard::Enter && !registration.playerName.empty()) {
                                            playerName = registration.textbox->getText();
                                            registrationComplete = true;
                                            RegistrationWindow.close();
                                        }
                                    }
                                    registration.handleInput(aevent);
                                }

                                
                                RegistrationWindow.clear();
                                registration.displayInformation(RegistrationWindow);
                                RegistrationWindow.display();
                            }
                        }

                        else if (menuSelection == 3) {
                            MENU.close();
                        }
                    }
                }
            }

            MENU.clear();
            MENU.draw(background);
            mainMenu.draw(MENU);
            MENU.display();
        }
    }
    return 0;
}