#include "board.hpp"

#define EMPTY ' '
// Cores dos jogadores
#define RED "\033[31m"
#define YELLOW "\033[33m"
// Cor do tabuleiro
#define BLUE "\033[34m"
// reinicia cores (previne imprimir tudo de uma cor)
#define RESET "\033[0m"

#define ROW_REQUIRED_TO_WIN 3
#define COLUMN_REQUIRED_TO_WIN 3

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
      this->printArenaColorHelper(this->arena[i][j]);
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
void board::printArenaColorHelper(const char &playerColor) const {
  if (playerColor == 'A') {
    cout << YELLOW << "●" << RESET;
  } else if (playerColor == 'V') {
    cout << RED << "●" << RESET;
  } else {
    cout << playerColor;
  }
}
void board::updateArena(const int &moveColunm, const char &playerColor) {
  for (int i = ROWS - 1; i > -1; --i) {
    if (this->arena[i][moveColunm] == EMPTY) {
      this->arena[i][moveColunm] = playerColor;
      break;
    }
  }
}
bool board::checkUpdateArena(const int &moveColunm) const {
  return (checkColunmOutOfBounds(moveColunm) && checkFullColunm(moveColunm));
}
bool board::checkColunmOutOfBounds(const int &moveColunm) const {
  if (moveColunm > COLUMNS || moveColunm < 0) {
    cout << "Jogada Inválida.\n"
            "Você inseriu um número fora do intervalo de validade!\n"
            "Insira um número de 0 a 6"
         << endl;
    return 0;
  }
  return 1;
}
bool board::checkFullColunm(const int &moveColunm) const {
  for (int i = 0; i < ROWS; ++i) {
    if (moveColunm == i) {
      if (this->arena[0][moveColunm] != EMPTY) {
        cout << "Jogada Inválida.\n"
                "Você tentou jogar numa coluna cheia!\n"
                "Escolha outra coluna"
             << endl;
        return 0;
      }
    }
  }
  return 1;
}
bool board::checkWin(const char &playerColor) const {
  return (checkWinRow(playerColor)) || checkWinColunm(playerColor);
}
bool board::checkWinRow(const char &playerColor) const {
  for (int i = ROWS - 1; i >= 0; --i) {
    // You can't win a row if your character isn't in it's colunm #3
    if (this->arena[i][COLUMN_REQUIRED_TO_WIN] != playerColor) {
      continue;
    }
    for (int j = 0; j <= COLUMN_REQUIRED_TO_WIN; ++j) {
      if (this->arena[i][j] == playerColor) {
        if (this->checkWinRowHelper(playerColor, i, j)) {
          return 1;
        }
      }
    }
  }
  return 0;
}
bool board::checkWinRowHelper(const char &playerColor, const int &i,
                              const int &j) const {
  for (int k = j; k <= j + 3; ++k) {
    if (this->arena[i][k] != playerColor) {
      break;
    }
    if (k == j + 3) {
      return 1;
    }
  }
  return 0;
}
bool board::checkWinColunm(const char &playerColor) const {
  for (int j = 0; j < COLUMNS; ++j) {
    // You can't win a colunm if your character isn't in it's row #3
    if (this->arena[ROW_REQUIRED_TO_WIN][j] != playerColor) {
      continue;
    }
    for (int i = ROWS - 1; i >= COLUMN_REQUIRED_TO_WIN; --i) {
      // There's no need to check rows above empty ones
      if (this->arena[i][j] == EMPTY) {
        continue;
      }
      if (this->arena[i][j] == playerColor)
        if (checkWinColunmHelper(playerColor, i, j)) {
          return 1;
        }
    }
  }
  return 0;
}
bool board::checkWinColunmHelper(const char &playerColor, const int &i,
                                 const int &j) const {
  for (int k = i; k >= i - 3; --k) {
    if (this->arena[k][j] != playerColor) {
      break;
    }
    if (k == i - 3) {
      return 1;
    }
  }
  return 0;
}
