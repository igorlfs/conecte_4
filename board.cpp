#include "board.hpp"
#define RESET "\033[0m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define EMPTY ' '
#include <iostream>
using std::cout;
using std::endl;
void board::initializeArena() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            this->arena[i][j] = EMPTY;
        }
    }
}
void board::printArena() const {
    this->printHeader();
    for (int i = 0; i < ROWS; ++i) {
        if (i != ROWS) this->printSeparator();
        for (int j = 0; j < COLUMNS; ++j) {
            cout << this->arena[i][j];
            if (j != COLUMNS - 1) cout << " │ ";
        }
        cout << endl;
    }
    cout << endl;
}
void board::printHeader() const {
    for (int i = 0; i < COLUMNS; ++i) {
        cout << i;
        if (i != COLUMNS - 1) cout << " │ ";
    }
    cout << endl;
}
void board::printSeparator() const {
    for (int i = 0; i < COLUMNS; ++i) {
        if (i == 0)
            cout << "──┼";
        else if (i == COLUMNS - 1)
            cout << "──";
        else
            cout << "───┼";
    }
    cout << endl;
}
void board::checkUpdateArena(int moveColunm) const {
    if (moveColunm > COLUMNS || moveColunm < 0) {
        cout << "Jogada Inválida.\n"
                "Você inseriu um número fora do intervalo de validade!\n"
                "Insira um número de 0 a 6"
             << endl;
    }
    for (int i = 0; i < ROWS; ++i) {
        if (moveColunm == i) {
            if (this->arena[ROWS - 1][moveColunm] != EMPTY) {
                cout << "Jogada Inválida.\n"
                        "Você tentou jogar numa coluna cheia!\n"
                        "Escolha outra coluna"
                     << endl;
            }
        }
    }
}
void board::updateArena(int moveColunm, char player) {
    for (int i = 0; i < COLUMNS; ++i) {
        if (i == moveColunm) {
            for (int j = ROWS; j > -1; --j) {
                if (this->arena[j][i] == EMPTY) {
                    this->arena[j][i] = player;
                    break;
                }
                if (j == 0) {
                    this->arenaFullHandler();
                }
            }
        }
    }
}
void board::arenaFullHandler() const { return; }
