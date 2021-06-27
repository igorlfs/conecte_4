#include "board.hpp"

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;

#define MAX_JOGADAS 42

char leJogador();
char outroJogador(char jogador1);
void jogue(char *jogador, board tabuleiro);

int main() {
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
    string input;
    cout << "Escolha sua cor:\n(" << COLOR_1 << ") para Amarelo\n(" << COLOR_2
         << ") para Vermelho\n";
    getline(cin, input);
    if (!input.find(COLOR_1)) {
      jogador = input[input.find(COLOR_1)];
    } else if (!input.find(COLOR_2)) {
      jogador = input[input.find(COLOR_2)];
    }
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
    cout << "Vez do jogador " << jogadorAtual + 1 << " ";
    if (jogador[jogadorAtual] == COLOR_1) {
      cout << '(' << YELLOW << "●" << RESET << ')';
    } else {
      cout << '(' << RED << "●" << RESET << ')';
    }
    cout << endl << "Escolha uma coluna: ";
    string input;
    int jogada;
    // Human counting is read (ie, starting at 1)
    // Later converted to computer counting (starting at 0)
    getline(cin, input);
    jogada = stoi(input);
    if (tabuleiro.checkUpdateArena(jogada - 1) && cin.good()) {
      tabuleiro.updateArena(jogada - 1, jogador[jogadorAtual]);
      tabuleiro.printArena();
      if (tabuleiro.checkWin(jogador[jogadorAtual])) {
        cout << jogadorAtual + 1 << " venceu!\n";
        break;
      }
      numJogadas++;
      if (numJogadas == MAX_JOGADAS) {
        cout << "O jogo empatou!" << endl;
      }
    }
  }
}
