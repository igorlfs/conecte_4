#pragma once
class board {
private:
  static const int ROWS = 6;
  static const int COLUMNS = 7;
  char arena[ROWS][COLUMNS];

  void printHeader() const;
  void printArenaColorHelper(char playerColor) const;
  void printSeparator() const;
  bool checkFullColunm(int moveColunm) const;
  bool checkColunmOutOfBounds(int moveColunm) const;
  bool checkWinColunm(char playerColor) const;
  bool checkWinRow(char playerColor) const;

public:
  board();
  void printArena() const;
  bool checkUpdateArena(int moveColunm) const;
  void updateArena(int moveColunm, char playerColor);
  bool checkWin(char playerColor) const;
};
