#include "board.hpp"

#include <assert.h>
#include <iostream>

using namespace std;

board::board() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) this->arena[i][j] = EMPTY;
    }
    this->printArena();
}
void board::printArena() const {
    this->printHeader();
    for (int i = 0; i < ROWS; ++i) {
        this->printSeparator();
        for (int j = 0; j < COLUMNS; ++j) {
            this->printArenaColorHelper(this->arena[i][j]);
            if (j != COLUMNS - 1) std::cout << BLUE " │ " << RESET;
        }
        std::cout.put('\n');
    }
    std::cout.put('\n');
}

void board::printHeader() const {
    for (int i = 1; i < COLUMNS + 1; ++i) {
        std::cout << i;
        if (i != COLUMNS) std::cout << BLUE << " │ " << RESET;
    }
    std::cout.put('\n');
}

void board::printSeparator() const {
    for (int i = 0; i < COLUMNS; ++i) {
        if (i == 0)
            std::cout << BLUE << "──┼" << RESET;
        else if (i == COLUMNS - 1)
            std::cout << BLUE << "──" << RESET;
        else
            std::cout << BLUE << "───┼" << RESET;
    }
    std::cout.put('\n');
}

void board::printArenaColorHelper(const char &playerColor) const {
    if (playerColor == CHAR_YELLOW)
        std::cout << YELLOW << BALL << RESET;
    else if (playerColor == CHAR_RED)
        std::cout << RED << BALL << RESET;
    else
        std::cout << playerColor;
}

void board::updateArena(const int &moveColumn, const char &playerColor) {
    // Assert the move is valid
    assert(this->checkUpdateArena(moveColumn));
    for (int i = ROWS - 1; i >= 0; --i) {
        if (this->arena[i][moveColumn] == EMPTY) {
            this->arena[i][moveColumn] = playerColor;
            return;
        }
    }
}

bool board::checkUpdateArena(const int &moveColumn) const {
    return (checkColumnOutOfBounds(moveColumn) && checkFullColumn(moveColumn));
}

bool board::checkColumnOutOfBounds(const int &moveColumn) const {
    if ((moveColumn > COLUMNS - 1) || (moveColumn < 0)) {
        std::cout << "Jogada Inválida.\n"
                     "Você inseriu um número inválido!\n"
                     "Insira um número de 1 a 7.\n";
        return 0;
    }
    return 1;
}

bool board::checkFullColumn(const int &moveColumn) const {
    if (this->arena[0][moveColumn] != EMPTY) {
        std::cout << "Jogada Inválida.\n"
                     "Você tentou jogar numa coluna cheia!\n"
                     "Escolha outra coluna.\n";
        return 0;
    }
    return 1;
}

bool board::checkWin(const char &playerColor) const {
    return (checkWinRow(playerColor) || checkWinCol(playerColor) ||
            checkWinPrimaryDiagonals(playerColor) ||
            checkWinSecondaryDiagonals(playerColor));
}

bool board::checkWinRow(const char &playerColor) const {
    for (int i = ROWS - 1; i > -1; --i) {
        // You can't win a row if your character isn't in it's column #3
        // Or else you can only fill 3 columns (either before or after)
        // This property relies on a 6x7 arena
        if (this->arena[i][3] != playerColor) continue;
        // Likewise, there's no need to check further than column 3
        for (int j = 0; j <= 3; ++j) {
            if (this->arena[i][j] == playerColor) {
                if (this->checkWinHelper(playerColor, i, j, row)) return 1;
            }
        }
    }
    return 0;
}

bool board::checkWinCol(const char &playerColor) const {
    for (int j = 0; j < COLUMNS; ++j) {
        // You can't win a column if your character isn't in it's row #3
        // Or else you can only fill 3 rows
        if (this->arena[3][j] != playerColor) continue;
        for (int i = ROWS - 1; i >= 3; --i) {
            // There's no need to check rows above empty ones
            if (this->arena[i][j] == EMPTY) continue;
            if (this->arena[i][j] == playerColor) {
                if (checkWinHelper(playerColor, i, j, col)) return 1;
            }
        }
    }
    return 0;
}

bool board::checkWinPrimaryDiagonals(const char &playerColor) const {
    // You can only connect X on a primary diagonal if it's "start" is in
    // the matrix's top left. More specifically, the bounds are given by
    // subtracting the number of elements you want to connect (eg, 4) from the
    // matrix's dimensions (eg, 6x7)
    for (int i = 0; i <= ROWS - CONNECT; i++) {
        for (int j = 0; j <= COLUMNS - CONNECT; j++) {
            if (this->arena[i][j] == playerColor) {
                if (checkWinHelper(playerColor, i, j, pri)) return 1;
            }
        }
    }
    return 0;
}

bool board::checkWinSecondaryDiagonals(const char &playerColor) const {
    // You can only connect X on a secondary diagonal if it's "start" is in
    // the matrix's bottom left. Look at primary for bounds explanation.
    for (int i = ROWS - 1; i > ROWS - CONNECT; --i) {
        for (int j = 0; j <= COLUMNS - CONNECT; j++) {
            if (this->arena[i][j] == playerColor) {
                if (checkWinHelper(playerColor, i, j, sec)) return 1;
            }
        }
    }
    return 0;
}

bool board::checkWinHelper(const char &color, const int &i, const int &j,
                           const winTypes &winType) const {
    for (int k = 1; k < CONNECT; ++k) {
        if ((winType == row) && (this->arena[i][j + k] != color)) break;
        if ((winType == col) && (this->arena[i - k][j] != color)) break;
        if ((winType == pri) && (this->arena[i + k][j + k] != color)) break;
        if ((winType == sec) && (this->arena[i - k][j + k] != color)) break;
        if (k == CONNECT - 1) return 1;
    }
    return 0;
}
