#include "board.hpp"

#include <iostream>
#include <string>

using namespace std;

char leJogador();
char outroJogador(char jogador1);
void jogue(char *jogador, board tabuleiro);

int main() {
  board tabuleiro;
  char jogador[2];

  jogador[0] = leJogador();
  jogador[1] = outroJogador(jogador[0]);
  jogue(jogador, tabuleiro);
  return 0;
}

char leJogador() {
  char jogador = '\0';
  do {
    string input;
    cout << "Escolha sua cor:\n(" << CHAR_YELLOW << ") para Amarelo\n("
         << CHAR_RED << ") para Vermelho\n";
    getline(cin, input);
    if (!input.find(CHAR_YELLOW)) {
      jogador = input[input.find(CHAR_YELLOW)];
    } else if (!input.find(CHAR_RED)) {
      jogador = input[input.find(CHAR_RED)];
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

  while (numJogadas < board::MAX_JOGADAS) {
    int jogadorAtual = numJogadas % 2;
    cout << "Vez do jogador " << jogadorAtual + 1 << " ";
    if (jogador[jogadorAtual] == CHAR_YELLOW) {
      cout << '(' << YELLOW << BALL << RESET << ')';
    } else {
      cout << '(' << RED << BALL << RESET << ')';
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
      if (numJogadas == board::MAX_JOGADAS) {
        cout << "O jogo empatou!" << endl;
      }
    }
  }
}
