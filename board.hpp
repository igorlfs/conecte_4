#pragma once
class board {
private:
  static const int ROWS = 6;
  static const int COLUMNS = 7;
  char arena[ROWS][COLUMNS];

  void printHeader() const;
  void printArenaColorHelper(const char &playerColor) const;
  void printSeparator() const;
  bool checkFullColunm(const int &moveColunm) const;
  bool checkColunmOutOfBounds(const int &moveColunm) const;
  bool checkWinColunm(const char &playerColor) const;
  bool checkWinRow(const char &playerColor) const;
  bool checkWinRowHelper(const char &playerColor, const int &i,
                         const int &j) const;

public:
  board();
  void printArena() const;
  bool checkUpdateArena(const int &moveColunm) const;
  void updateArena(const int &moveColunm, const char &playerColor);
  bool checkWin(const char &playerColor) const;
};
