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
  // Cores
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
    cin >> jogada;
    if (tabuleiro.checkUpdateArena(jogada) && cin.good()) {
      tabuleiro.updateArena(jogada, jogador[jogadorAtual]);
      tabuleiro.printArena();
      numJogadas++;
    }
  }
}
