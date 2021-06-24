#pragma once
#define ROWS 6
#define COLUMNS 7
class board {
private:
  char arena[ROWS][COLUMNS];

  void printHeader() const;
  void printArenaColorHelper(const char &playerColor) const;
  void printSeparator() const;
  bool checkFullColunm(const int &moveColunm) const;
  bool checkColunmOutOfBounds(const int &moveColunm) const;
  bool checkWinLines(const char &playerColor) const;
  bool checkWinCol(const char &playerColor) const;
  bool checkWinColHelper(const char &playerColor, const int &i,
                         const int &j) const;
  bool checkWinRow(const char &playerColor) const;
  bool checkWinRowHelper(const char &playerColor, const int &i,
                         const int &j) const;
  bool checkWinDiagonals(const char &playerColor) const;
  bool checkWinPrimaryDiagonals(const char &playerColor) const;
  bool checkWinPrimaryDiagonalsHelper(const char &playerColor, const int &i,
                                      const int &j) const;
  bool checkWinSecondaryDiagonals(const char &playerColor) const;
  bool checkWinSecondaryDiagonalsHelper(const char &playerColor, const int &i,
                                        const int &j) const;

public:
  board();
  void printArena() const;
  bool checkUpdateArena(const int &moveColunm) const;
  void updateArena(const int &moveColunm, const char &playerColor);
  bool checkWin(const char &playerColor) const;
};
