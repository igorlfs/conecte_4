#include "board.hpp"

#include "input.hpp"
#include <iostream>
#include <regex>
#include <string>

using namespace std;

char readPlayer();
void play(char *jogador, Board::grid tabuleiro);

int main() {
    Board::grid grid;
    char player[2];

    player[0] = readPlayer();
    (player[0] == 'A') ? player[1] = 'V' : player[1] = 'A';
    play(player, grid);
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

void play(char *player, Board::grid grid) {
    int numMoves = 0;

    while (numMoves < Board::grid::MAX_JOGADAS) {
        int currentPlayer = numMoves % 2;
        cout << "Vez do jogador " << currentPlayer + 1 << " ";
        (player[currentPlayer] == CHAR_YELLOW)
            ? cout << '(' << YELLOW << CHAR_YELLOW << RESET << ')'
            : cout << '(' << RED << CHAR_RED << RESET << ')';
        cout << endl << "Escolha uma coluna: ";
        string input;
        int jogada;
        getline(cin, input);
        jogada = stoi(input);
        if (grid.checkUpdateArena(jogada - 1) && cin.good()) {
            grid.updateArena(jogada - 1, player[currentPlayer]);
            grid.printArena();
            if (grid.checkWin(player[currentPlayer])) {
                cout << currentPlayer + 1 << " venceu!\n";
                return;
            }
            numMoves++;
            if (numMoves == Board::grid::MAX_JOGADAS)
                cout << "O jogo empatou!" << endl;
        }
    }
}
