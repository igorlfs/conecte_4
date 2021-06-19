#include "board.hpp"
int main() {
    board tabuleiro;
    tabuleiro.initializeArena();
    for (int i = 0; i < 10; ++i) {
        tabuleiro.updateArena(0, 'X');
    }
    tabuleiro.printArena();
    return 0;
}
