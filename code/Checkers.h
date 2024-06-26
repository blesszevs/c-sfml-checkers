#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum PieceColor { RED, BLUE, NONE };

class Piece {
public:
    PieceColor color;
    bool isKing;
    int row;
    int col;
    sf::CircleShape shape;
    sf::Color outlineColor;

    Piece(PieceColor color = NONE, int row = -1, int col = -1);
    void setKing(bool king);
    void draw(sf::RenderWindow& window);

};

class Checkers {
public:
    static const int boardSize = 8;  
    std::vector<Piece> board;      
    PieceColor winner;
    Checkers();
    sf::Font font;
    sf::Text winnerText;
    void draw(sf::RenderWindow& window);
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol);
    void makeMove(int fromRow, int fromCol, int toRow, int toCol);
    void handleMouseClick(int mouseX, int mouseY);
    bool isValidJump(int fromRow, int fromCol, int toRow, int toCol);
    bool checkWinCondition();
    bool hasJumpAvailable(PieceColor player);
    std::string playerName; 
    std::string opponentName;
    bool isDraw();
private:
    sf::Text turnText;
    bool jumped = false;
    PieceColor currentPlayer = RED;
    int selectedRow = -1;
    int selectedCol = -1;
};