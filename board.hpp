#ifndef BOARD_H
#define BOARD_H
#include <cassert>

// Colors
#define YELLOW "\033[33m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define RESET "\033[0m"

// Special characters
static const char *BALL = "⬤";

static constexpr char CHAR_YELLOW = 'A';
static constexpr char CHAR_RED = 'V';

namespace Board {

static constexpr char EMPTY = ' ';

enum winTypes { row, col, pri, sec };

class grid {
  public:
    static constexpr int ROWS = 6;
    static constexpr int COLS = 7;
    static constexpr int MAX_JOGADAS = ROWS * COLS;
    static constexpr int CONNECT = 4;

    // Fill grid with EMPTY
    grid();

    void printArena() const;

    bool checkWin(const char &playerColor) const;

    void updateArena(const int &moveColunm, const char &playerColor);
    char getCell(const int &i, const int &j) const {
        assert(i >= 0 && i < ROWS && j >= 0 && j < COLS);
        return this->arena[i][j];
    }

  private:
    char arena[ROWS][COLS];

    void printHeader() const;
    void printArenaColorHelper(const char &playerColor) const;
    void printSeparator() const;

    bool checkWinRow(const char &playerColor) const;
    bool checkWinCol(const char &playerColor) const;
    bool checkWinPrimaryDiagonals(const char &playerColor) const;
    bool checkWinSecondaryDiagonals(const char &playerColor) const;
    bool checkWinHelper(const char &playerColor, const int &i, const int &j,
                        const winTypes &winType) const;
};
} // namespace Board
#endif
