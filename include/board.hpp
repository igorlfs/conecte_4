#pragma once

#define YELLOW "\033[33m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define RESET "\033[0m" // prevents printing everything the same color

#define CHAR_YELLOW 'A'
#define CHAR_RED 'V'

#define BALL "⬤"

enum winTypes {
    row,
    col,
    primary,
    secondary,
};

class board {
  public:
    static constexpr int ROWS = 6;
    static constexpr int COLUMNS = 7;
    static constexpr int MAX_JOGADAS = ROWS * COLUMNS;
    static constexpr int CONNECT = 4;

    static constexpr char EMPTY = ' ';

    board();
    void printArena() const;
    bool checkUpdateArena(const int &moveColunm) const;
    void updateArena(const int &moveColunm, const char &playerColor);
    bool checkWin(const char &playerColor) const;
    void setPlayers(const char &player, const int &i);
    char getPlayers(const int &i) const;

  private:
    char arena[ROWS][COLUMNS];
    char players[2];

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
};
