#include "board.hpp"
#include <iostream>
using std::cin;
using std::cout;
#define MAX_JOGADAS 42
char leJogador();
char outroJogador(char jogador1);
void jogue(char *jogador, board tabuleiro);
int main() {
  // Todo:
  // Bugs de leitura
  // Checar condição de vitória
  board tabuleiro;
  char jogador[2];
  jogador[0] = leJogador();
  jogador[1] = outroJogador(jogador[0]);
  tabuleiro.printArena();
  jogue(jogador, tabuleiro);
  return 0;
}
char leJogador() {
  char jogador;
  do {
    cout << "Escolha sua cor:\n"
            "(A) para Amarelo\n"
            "(V) para Vermelho\n";
    cin >> jogador;
  } while (jogador != 'A' && jogador != 'V');
  return jogador;
}
char outroJogador(char jogador1) {
  if (jogador1 == 'A') {
    return 'V';
  } else {
    return 'A';
  }
}
void jogue(char *jogador, board tabuleiro) {
  int numJogadas = 0;
  while (numJogadas < MAX_JOGADAS) {
    int jogadorAtual = numJogadas % 2;
    cout << "Vez do jogador " << jogadorAtual + 1 << ".\nEscolha uma coluna: ";
    int jogada;
    // Human counting is read (ie, starting at 1)
    // Later converted to computer counting (starting at 0)
    cin >> jogada;
    if (tabuleiro.checkUpdateArena(jogada - 1) && cin.good()) {
      tabuleiro.updateArena(jogada - 1, jogador[jogadorAtual]);
      tabuleiro.printArena();
      if (tabuleiro.checkWin(jogador[jogadorAtual])) {
        cout << jogadorAtual + 1 << " venceu!\n";
        break;
      }
      numJogadas++;
    }
  }
}
