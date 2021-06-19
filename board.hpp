#pragma once
class board {
   private:
    static const int ROWS = 6;
    static const int COLUMNS = 7;
    char arena[ROWS][COLUMNS];

    void printHeader() const;
    void printSeparator() const;
    void arenaFullHandler() const;
    bool checkFullColunm(int moveColunm) const;
    bool checkColunmOutOfBounds(int moveColunm) const;

   public:
    void initializeArena();
    void printArena() const;
    bool checkUpdateArena(int moveColunm) const;
    void updateArena(int moveColunm, char player);
};
