#include "board.hpp"

#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define RESET "\033[0m" // prevents printing everything the same color

#define EMPTY ' '

#define COL_REQUIRED_TO_WIN 3
#define ROW_REQUIRED_TO_WIN 3
#define ROW_DIAGONAL ROWS - CONNECT
#define MAX_COL_DIAGONAL COLUMNS - CONNECT

#include <assert.h>
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
    this->printSeparator();
    for (int j = 0; j < COLUMNS; ++j) {
      this->printArenaColorHelper(this->arena[i][j]);
      // Do not print a separator in the last colunm
      if (j != COLUMNS - 1) {
        cout << BLUE " │ " << RESET;
      }
    }
    cout << endl;
  }
  cout << endl;
}
void board::printHeader() const {
  // Print natural counting header (starting at 1)
  for (int i = 1; i < COLUMNS + 1; ++i) {
    cout << i;
    if (i != COLUMNS) {
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
  // Assert the move is valid
  assert(this->checkUpdateArena(moveColunm));
  for (int i = ROWS - 1; i >= 0; --i) {
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
  if (moveColunm > COLUMNS - 1 || moveColunm < 0) {
    cout << "Jogada Inválida.\n"
            "Você inseriu um número inválido!\n"
            "Insira um número de 1 a 7."
         << endl;
    return 0;
  }
  return 1;
}
bool board::checkFullColunm(const int &moveColunm) const {
  if (this->arena[0][moveColunm] != EMPTY) {
    cout << "Jogada Inválida.\n"
            "Você tentou jogar numa coluna cheia!\n"
            "Escolha outra coluna."
         << endl;
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
    // You can't win a row if your character isn't in it's colunm #3
    // Or else you can only fill 3 colunms (either before or after)
    // (obviously not being able to connect 4)
    // This property relies on a 6x7 arena
    if (this->arena[i][COL_REQUIRED_TO_WIN] != playerColor) {
      continue;
    }
    // Likewise, there's no need to check further than colunm 3
    for (int j = 0; j <= COL_REQUIRED_TO_WIN; ++j) {
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
  for (int k = 1; k < CONNECT; ++k) {
    if (this->arena[i][j + k] != playerColor) {
      break;
    }
    if (k == CONNECT - 1) {
      return 1;
    }
  }
  return 0;
}
bool board::checkWinCol(const char &playerColor) const {
  for (int j = 0; j < COLUMNS; ++j) {
    // You can't win a colunm if your character isn't in it's row #3
    // Or else you can only fill 3 rows
    if (this->arena[ROW_REQUIRED_TO_WIN][j] != playerColor) {
      continue;
    }
    for (int i = ROWS - 1; i >= ROW_REQUIRED_TO_WIN; --i) {
      // There's no need to check rows above empty ones
      if (this->arena[i][j] == EMPTY) {
        continue;
      }
      if (this->arena[i][j] == playerColor)
        if (checkWinColHelper(playerColor, i, j)) {
          return 1;
        }
    }
  }
  return 0;
}
bool board::checkWinColHelper(const char &playerColor, const int &i,
                              const int &j) const {
  for (int k = 1; k < CONNECT; ++k) {
    if (this->arena[i - k][j] != playerColor) {
      break;
    }
    if (k == CONNECT - 1) {
      return 1;
    }
  }
  return 0;
}
bool board::checkWinPrimaryDiagonals(const char &playerColor) const {
  // You can only connect X on a primary diagonal if it's start is in
  // the matrix's top left. More specifically, the bounds are given by
  // subtracting the number of elements you want to connect (eg, 4) from the
  // matrix's dimensions (eg, 6x7)
  for (int i = 0; i <= ROW_DIAGONAL; i++) {
    for (int j = 0; j <= MAX_COL_DIAGONAL; j++) {
      if (this->arena[i][j] == playerColor) {
        if (checkWinPrimaryDiagonalsHelper(playerColor, i, j)) {
          return 1;
        }
      }
    }
  }
  return 0;
}
bool board::checkWinPrimaryDiagonalsHelper(const char &playerColor,
                                           const int &i, const int &j) const {
  for (int k = 1; k < CONNECT; ++k) {
    if (this->arena[i + k][j + k] != playerColor) {
      break;
    }
    if (k == CONNECT - 1) {
      return 1;
    }
  }
  return 0;
}
bool board::checkWinSecondaryDiagonals(const char &playerColor) const {
  // You can only connect X on a secondary diagonal if it's start is in
  // the matrix's bottom left. More specifically, the bound are given by
  // subtracting the number of elements you want to connect (eg, 4) from the
  // matrix's dimensions (eg, 6x7)
  for (int i = ROWS - 1; i > ROW_DIAGONAL; --i) {
    for (int j = 0; j <= MAX_COL_DIAGONAL; j++) {
      if (this->arena[i][j] == playerColor) {
        if (checkWinSecondaryDiagonalsHelper(playerColor, i, j)) {
          return 1;
        }
      }
    }
  }
  return 0;
}
bool board::checkWinSecondaryDiagonalsHelper(const char &playerColor,
                                             const int &i, const int &j) const {
  for (int k = 1; k < CONNECT; ++k) {
    if (this->arena[i - k][j + k] != playerColor) {
      break;
    }
    if (k == CONNECT - 1) {
      return 1;
    }
  }
  return 0;
}
