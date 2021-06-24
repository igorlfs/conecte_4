#pragma once

#define ROWS 6
#define COLUMNS 7
#define CONNECT 4

enum winTypes {
  row,
  col,
  primary,
  secondary,
};

class board {

private:
  char arena[ROWS][COLUMNS];

  void printHeader() const;
  void printArenaColorHelper(const char &playerColor) const;
  void printSeparator() const;

  bool checkFullColumn(const int &moveColunm) const;
  bool checkColumnOutOfBounds(const int &moveColunm) const;

  bool checkWinRow(const char &playerColor) const;
  bool checkWinCol(const char &playerColor) const;
  bool checkWinPrimaryDiagonals(const char &playerColor) const;
  bool checkWinSecondaryDiagonals(const char &playerColor) const;
  bool checkWinHelper(const char &playerColor, const int &i, const int &j,
                      const winTypes &winType) const;

public:
  board();
  void printArena() const;
  bool checkUpdateArena(const int &moveColunm) const;
  void updateArena(const int &moveColunm, const char &playerColor);
  bool checkWin(const char &playerColor) const;
};
