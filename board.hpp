#pragma once
class board {
   private:
    static const int ROWS = 6;
    static const int COLUMNS = 7;
    char arena[ROWS][COLUMNS];

    void printHeader() const;
    void printSeparator() const;
    void arenaFullHandler() const;

   public:
    void initializeArena();
    void printArena() const;
    void updateArena(int moveColunm, char player);
};
