#include "board.hpp"
#include <iostream>
using std::cin;
using std::cout;
char leJogador();
char outroJogador(char jogador1);
int main() {
  // Todo:
  // Leitura das entradas
  // Checar condição de vitória
  board tabuleiro;
  char jogador1 = leJogador();
  char jogador2 = outroJogador(jogador1);
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
