#ifndef BOARD_H
#define BOARD_H

// Colors
#define YELLOW "\033[33m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define RESET "\033[0m"

// Special characters
#define BALL "⬤"

static constexpr char CHAR_YELLOW = 'A';
static constexpr char CHAR_RED = 'V';

namespace Board {
enum winTypes {
    row,
    col,
    pri,
    sec,
};

class grid {
  public:
    static constexpr int ROWS = 6;
    static constexpr int COLUMNS = 7;
    static constexpr int MAX_JOGADAS = ROWS * COLUMNS;
    static constexpr int CONNECT = 4;

    static constexpr char EMPTY = ' ';

    grid();
    void printArena() const;
    bool checkUpdateArena(const int &moveColunm) const;
    void updateArena(const int &moveColunm, const char &playerColor);
    bool checkWin(const char &playerColor) const;
    void setPlayers(const char &player, const int &i) {
        this->players[i] = player;
    }
    char getPlayers(const int &i) const { return this->players[i]; }

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
} // namespace Board
#endif
