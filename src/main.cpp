#include "board.hpp"

#include "input.hpp"
#include <iostream>
#include <regex>
#include <string>

using namespace std;

char readPlayer();
void jogue(char *jogador, board tabuleiro);

int main() {
    board grid;
    char jogador[2];

    jogador[0] = readPlayer();
    (jogador[0] == 'A') ? jogador[1] = 'V' : jogador[1] = 'A';
    jogue(jogador, grid);
    return 0;
}

char readPlayer() {
chooseColorAgain:
    try {
        std::regex expectedFormat("\\s*\\w\\s*");
        std::string readLine;
        cout << "Escolha sua cor ('A' para Amarelo ou 'V' para Vermelho): ";
        std::getline(std::cin, readLine);
        if (std::cin.eof()) throw Input::interrupt();
        if (readLine.empty()) throw Input::emptyLine();
        if (!std::regex_match(readLine, expectedFormat))
            throw Input::invalidColorFormat{readLine};
        char colorInitial;
        std::stringstream ss(readLine);
        ss >> colorInitial;
        if (colorInitial != 'A' && colorInitial != 'V')
            throw Input::invalidColor{readLine};
        return colorInitial;
    } catch (Input::interrupt e) {
        std::cout << "\n\nA entrada de dados foi interrompida. Saindo.\n\n";
        exit(1);
    } catch (Input::emptyLine e) {
        std::cout << "\nNão foi informado nenhum dado."
                  << "\nPor favor, insira uma cor.\n\n";
        goto chooseColorAgain;
    } catch (Input::invalidColorFormat e) {
        std::cout << "\nEntrada inválida: " << e.str
                  << "\nA cor deve ser uma ÚNICA letra minúscula, a inicial da "
                     "cor desejada\n\n";
        goto chooseColorAgain;
    } catch (Input::invalidColor e) {
        std::cout << "\nEntrada inválida: " << e.str
                  << "\nA cor escolhida não está disponível.\n\n";
        goto chooseColorAgain;
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
