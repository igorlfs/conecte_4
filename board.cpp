#include "board.hpp"
#define RESET "\033[0m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define EMPTY ' '
#define VALID 1
#define INVALID 0

#include <iostream>
using std::cout;
using std::endl;
board::board() {
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLUMNS; ++j) {
      this->arena[i][j] = EMPTY;
    }
  }
}
void board::printArena() const {
  this->printHeader();
  for (int i = 0; i < ROWS; ++i) {
    if (i != ROWS) {
      this->printSeparator();
    }
    for (int j = 0; j < COLUMNS; ++j) {
      cout << this->arena[i][j];
      if (j != COLUMNS - 1) {
        cout << BLUE " │ " << RESET;
      }
    }
    cout << endl;
  }
  cout << endl;
}
void board::printHeader() const {
  for (int i = 0; i < COLUMNS; ++i) {
    cout << i;
    if (i != COLUMNS - 1) {
      cout << BLUE << " │ " << RESET;
    }
  }
  cout << endl;
}
void board::printSeparator() const {
  for (int i = 0; i < COLUMNS; ++i) {
    if (i == 0) {
      cout << BLUE << "──┼" << RESET;
    } else if (i == COLUMNS - 1) {
      cout << BLUE << "──" << RESET;
    } else {
      cout << BLUE << "───┼" << RESET;
    }
  }
  cout << endl;
}
void board::updateArena(int moveColunm, char player) {
  if (checkUpdateArena(moveColunm)) {
    for (int i = ROWS; i > -1; --i) {
      if (this->arena[i][moveColunm] == EMPTY) {
        this->arena[i][moveColunm] = player;
        break;
      }
    }
  }
}
bool board::checkUpdateArena(int moveColunm) const {
  return (checkColunmOutOfBounds(moveColunm) && checkFullColunm(moveColunm));
}
bool board::checkColunmOutOfBounds(int moveColunm) const {
  if (moveColunm > COLUMNS || moveColunm < 0) {
    cout << "Jogada Inválida.\n"
            "Você inseriu um número fora do intervalo de validade!\n"
            "Insira um número de 0 a 6"
         << endl;
    return INVALID;
  }
  return VALID;
}
bool board::checkFullColunm(int moveColunm) const {
  for (int i = 0; i < ROWS; ++i) {
    if (moveColunm == i) {
      if (this->arena[0][moveColunm] != EMPTY) {
        cout << "Jogada Inválida.\n"
                "Você tentou jogar numa coluna cheia!\n"
                "Escolha outra coluna"
             << endl;
        return INVALID;
      }
    }
  }
  return VALID;
}
