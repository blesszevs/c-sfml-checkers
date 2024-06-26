#include "Checkers.h"
#include <iostream>

Piece::Piece(PieceColor color, int row, int col) : outlineColor(sf::Color::Transparent), color(color), isKing(false), row(row), col(col) {
    shape.setRadius(20);
    shape.setPosition(col * 50 + 5, row * 50 + 5);
    if (color == RED) {
        shape.setFillColor(sf::Color::Red);
    }
    else if (color == BLUE) {
        shape.setFillColor(sf::Color::Blue);
    }
}

void Piece::setKing(bool king) {
    isKing = king;
}

void Piece::draw(sf::RenderWindow& window) {
    window.draw(shape);

    if (isKing) {
        sf::CircleShape highlight;
        highlight.setRadius(22);
        highlight.setPosition(col * 50 + 3, row * 50 + 3);
        highlight.setFillColor(sf::Color::Transparent);
        highlight.setOutlineThickness(2);
        highlight.setOutlineColor(outlineColor);
        window.draw(highlight);
    }
}

Checkers::Checkers() {
    board.resize(boardSize * boardSize);
    for (int row = 0; row < 3; ++row) {
        for (int col = (row + 1) % 2; col < boardSize; col += 2) {
            board[row * boardSize + col] = Piece(BLUE, row, col);
        }
    }
    for (int row = 5; row < boardSize; ++row) {
        for (int col = (row + 1) % 2; col < boardSize; col += 2) {
            board[row * boardSize + col] = Piece(RED, row, col);
        }
    }
    
    if (!font.loadFromFile("ARIAL.ttf")) {
        std::cout << "Error loading font!" << std::endl;
    }

    winnerText.setFont(font);
    winnerText.setCharacterSize(30);
    winnerText.setFillColor(sf::Color::White);
    winnerText.setPosition(sf::Vector2f(300, 100));

    turnText.setFont(font);
    turnText.setCharacterSize(30);
    turnText.setFillColor(sf::Color::White);
    turnText.setPosition(sf::Vector2f(100, 450));
    playerName = "";
    opponentName = "";
}

void Checkers::draw(sf::RenderWindow& window) {
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            sf::RectangleShape square;
            square.setSize(sf::Vector2f(50, 50));
            square.setPosition(col * 50, row * 50);
            if ((row + col) % 2 == 0) {
                square.setFillColor(sf::Color::White);
            }
            else {
                square.setFillColor(sf::Color::Black);
            }
            window.draw(square);

            if (board[row * boardSize + col].color != NONE) {
                board[row * boardSize + col].draw(window);
            }
        }
    }
    if (selectedRow != -1 && selectedCol != -1) {
        sf::CircleShape highlight;
        highlight.setRadius(22);
        highlight.setPosition(selectedCol * 50 + 3, selectedRow * 50 + 3);
        highlight.setFillColor(sf::Color::Transparent);
        highlight.setOutlineThickness(2);
        highlight.setOutlineColor(sf::Color::Yellow);
        window.draw(highlight);
    }
    window.draw(turnText);
    window.draw(winnerText);
}

bool Checkers::isValidJump(int fromRow, int fromCol, int toRow, int toCol) {
    if (fromRow < 0 || fromRow >= boardSize || fromCol < 0 || fromCol >= boardSize ||
        toRow < 0 || toRow >= boardSize || toCol < 0 || toCol >= boardSize) {
        return false;
    }

    Piece& piece = board[fromRow * boardSize + fromCol];
    if (piece.color == NONE || piece.color != currentPlayer) {
        return false;
    }

    if (board[toRow * boardSize + toCol].color != NONE) {
        return false;
    }

    int rowDiff = toRow - fromRow;
    int colDiff = toCol - fromCol;
    if (abs(rowDiff) != abs(colDiff)) {
        return false;
    }

    if (abs(rowDiff) != 2 || abs(colDiff) != 2) {
        return false;
    }
    int rowDirection = (rowDiff > 0) ? 1 : -1;
    int colDirection = (colDiff > 0) ? 1 : -1;

    int currentRow = fromRow + rowDirection;
    int currentCol = fromCol + colDirection;
    while (currentRow != toRow && currentCol != toCol) {
        if (board[currentRow * boardSize + currentCol].color == NONE ||
            board[currentRow * boardSize + currentCol].color == currentPlayer) {
            return false;
        }
        currentRow += rowDirection;
        currentCol += colDirection;
    }

    return true;
}

bool Checkers::isValidMove(int fromRow, int fromCol, int toRow, int toCol) {
    if (fromRow < 0 || fromRow >= boardSize || fromCol < 0 || fromCol >= boardSize ||
        toRow < 0 || toRow >= boardSize || toCol < 0 || toCol >= boardSize) {
        return false;
    }

    Piece& piece = board[fromRow * boardSize + fromCol];
    if (piece.color == NONE || piece.color != currentPlayer) {
        return false;
    }

    if (!jumped && board[toRow * boardSize + toCol].color != NONE) {
        return false;
    }

    int rowDiff = toRow - fromRow;
    int colDiff = toCol - fromCol;

    if (!jumped && hasJumpAvailable(currentPlayer)) {
        return isValidJump(fromRow, fromCol, toRow, toCol);
    }

    if (isValidJump(fromRow, fromCol, toRow, toCol)) {
        return true;
    }

    if (jumped) {
        return isValidJump(fromRow, fromCol, toRow, toCol);
    }

    if (piece.isKing) {
        return (abs(rowDiff) == abs(colDiff));
    }
    else {
        if (piece.color == RED) {
            return (rowDiff == -1 && abs(colDiff) == 1);
        }
        else {
            return (rowDiff == 1 && abs(colDiff) == 1);
        }
    }
}

void Checkers::makeMove(int fromRow, int fromCol, int toRow, int toCol) {
    if (isValidMove(fromRow, fromCol, toRow, toCol)) {
        board[toRow * boardSize + toCol] = board[fromRow * boardSize + fromCol];
        board[fromRow * boardSize + fromCol] = Piece();

        Piece& piece = board[toRow * boardSize + toCol];
        piece.row = toRow;
        piece.col = toCol;
        piece.shape.setPosition(toCol * 50 + 5, toRow * 50 + 5);

      
        if ((toRow == 0 && piece.color == RED) ||
            (toRow == boardSize - 1 && piece.color == BLUE)) {
            piece.setKing(true);
            piece.outlineColor = sf::Color::Green;
        }

        jumped = false;
        bool jumpMade = false;
        int rowDiff = toRow - fromRow;
        int colDiff = toCol - fromCol;

        if (abs(rowDiff) == abs(colDiff) && abs(rowDiff) > 1) {
            int rowDirection = (rowDiff > 0) ? 1 : -1;
            int colDirection = (colDiff > 0) ? 1 : -1;
            int currentRow = fromRow + rowDirection;
            int currentCol = fromCol + colDirection;

            while (currentRow != toRow && currentCol != toCol) {
                if (board[currentRow * boardSize + currentCol].color != currentPlayer) {
                    board[currentRow * boardSize + currentCol] = Piece();
                    jumpMade = true;
                }
                else {
                    std::cout << "Помилка: зустрілась власна шашка під час захоплення!" << std::endl;
                    return;
                }
                currentRow += rowDirection;
                currentCol += colDirection;
            }
        }

        if (jumpMade) {
            selectedRow = toRow;
            selectedCol = toCol;
        }

        if (jumpMade) {
            bool foundJump = false;
            for (int row = 0; row < boardSize; ++row) {
                for (int col = 0; col < boardSize; ++col) {
                    if (isValidJump(toRow, toCol, row, col)) {
                        jumped = true;
                        selectedRow = toRow;
                        selectedCol = toCol;
                        foundJump = true;
                        break;
                    }
                }
                if (foundJump) break;
            }

            if (!foundJump) {
                jumped = false;
                selectedRow = -1;
                selectedCol = -1;
                currentPlayer = (currentPlayer == RED) ? BLUE : RED;
            }
        }
        else {
            currentPlayer = (currentPlayer == RED) ? BLUE : RED;
            selectedRow = -1;
            selectedCol = -1;
        }
        if (currentPlayer == RED) {
            turnText.setString(playerName + "'s Turn");
        }
        else {
            turnText.setString(opponentName + "'s Turn");
        }

        if (isDraw()) {
            winner = NONE;
            winnerText.setString("Draw!");
            std::cout << "Нічия!" << std::endl;
        }
    }
}

bool Checkers::hasJumpAvailable(PieceColor player) {
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            if (board[row * boardSize + col].color == player) {
                for (int dirRow = -1; dirRow <= 1; dirRow += 2) {
                    for (int dirCol = -1; dirCol <= 1; dirCol += 2) {
                        if (isValidJump(row, col, row + 2 * dirRow, col + 2 * dirCol)) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

void Checkers::handleMouseClick(int mouseX, int mouseY) {
    int row = mouseY / 50;
    int col = mouseX / 50;

    if (selectedRow == -1 && board[row * boardSize + col].color != NONE) {
        if (!jumped || (row == selectedRow && col == selectedCol)) {
            selectedRow = row;
            selectedCol = col;
        }
    }
    else if (selectedRow != -1) {
        makeMove(selectedRow, selectedCol, row, col);
        if (!jumped) {
            selectedRow = -1;
            selectedCol = -1;
        }
    }
}
bool Checkers::checkWinCondition() {
    int redPieces = 0;
    int bluePieces = 0;

    for (int i = 0; i < boardSize * boardSize; ++i) {
        if (board[i].color == RED) {
            ++redPieces;
        }
        else if (board[i].color == BLUE) {
            ++bluePieces;
        }
    }

    if (redPieces == 0 || bluePieces == 0) {        
        if (redPieces == 0) {
            winner = BLUE;
        }
        else {
            winner = RED;
        }
        return true;
    }
    else if (isDraw()) {
 
        winner = NONE;
        return true;
    }

    return false;
}

bool Checkers::isDraw() {
   
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            if (board[row * boardSize + col].color == currentPlayer) {
            
                for (int toRow = 0; toRow < boardSize; ++toRow) {
                    for (int toCol = 0; toCol < boardSize; ++toCol) {
                        if (isValidMove(row, col, toRow, toCol)) {
                            
                            return false;
                        }
                    }
                }
                
                for (int dirRow = -1; dirRow <= 1; dirRow += 2) {
                    for (int dirCol = -1; dirCol <= 1; dirCol += 2) {
                        if (isValidJump(row, col, row + 2 * dirRow, col + 2 * dirCol)) {
                           
                            return false;
                        }
                    }
                }
            }
        }
    }


    winner = NONE;
    winnerText.setString("Draw!");
    return true;
}