#include "board.hpp"

#include "input.hpp"
#include <iostream>
#include <regex>
#include <string>

using namespace std;

char readPlayer();
uint readColumn(char jogador, Board::grid tabuleiro);

int main() {
    Board::grid grid;
    char player[2];

    player[0] = readPlayer();
    (player[0] == CHAR_YELLOW) ? player[1] = CHAR_RED : player[1] = CHAR_YELLOW;
    int numMoves = 0;
    while (numMoves < Board::grid::MAX_JOGADAS) {
        int currentPlayer = numMoves % 2;
        cout << "Vez do jogador " << currentPlayer + 1 << " ";
        (player[currentPlayer] == CHAR_YELLOW)
            ? cout << '(' << YELLOW << CHAR_YELLOW << RESET << ')'
            : cout << '(' << RED << CHAR_RED << RESET << ')';
        grid.updateArena(readColumn(player[currentPlayer], grid),
                         player[currentPlayer]);
        grid.printArena();
        if (grid.checkWin(player[currentPlayer])) {
            cout << currentPlayer + 1 << " venceu!\n";
            break;
        }
        numMoves++;
        if (numMoves == Board::grid::MAX_JOGADAS) cout << "O jogo empatou!\n";
    }
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
        if (!std::regex_match(readLine, expectedFormat))
            throw Input::invalidColorFormat();
        char colorInitial;
        std::stringstream ss(readLine);
        ss >> colorInitial;
        if (colorInitial != CHAR_YELLOW && colorInitial != CHAR_RED)
            throw Input::invalidColor{readLine};
        return colorInitial;
    } catch (Input::interrupt e) {
        std::cout << "\n\nA entrada de dados foi interrompida. Saindo.\n\n";
        exit(1);
    } catch (Input::invalidColorFormat e) {
        std::cout << "\nEntrada inválida."
                  << "\nA cor deve ser uma ÚNICA letra minúscula, a inicial da "
                     "cor desejada\n\n";
        goto chooseColorAgain;
    } catch (Input::invalidColor e) {
        std::cout << "\nEntrada inválida: " << e.str
                  << "\nA cor escolhida não está disponível.\n\n";
        goto chooseColorAgain;
    }
}

uint readColumn(char player, Board::grid grid) {
chooseNumberAgain:
    try {
        std::regex expectedFormat("\\s*\\d+\\s*");
        std::string readLine;
        cout << "\nEscolha uma coluna: ";
        std::getline(std::cin, readLine);
        if (std::cin.eof()) throw Input::interrupt();
        if (!std::regex_match(readLine, expectedFormat))
            throw Input::invalidNumberFormat();
        std::stringstream ss(readLine);
        uint column;
        ss >> column;
        if (column == 0) throw Input::numberOutOfBounds();
        column--;
        if ((column > Board::grid::COLS - 1)) throw Input::numberOutOfBounds();
        if (grid.getCell(0, column) != Board::EMPTY) throw Input::fullColumn();
        return column;
    } catch (Input::interrupt e) {
        std::cout << "\n\nA entrada de dados foi interrompida. Saindo.\n\n";
        exit(1);
    } catch (Input::invalidNumberFormat e) {
        std::cout << "\nEntrada inválida."
                  << "\nVocê deve escolher um ÚNICO NÚMERO natural\n";
        goto chooseNumberAgain;
    } catch (Input::numberOutOfBounds e) {
        std::cout << "Você inseriu um número inválido!\n"
                     "Insira um número de 1 a "
                  << Board::grid::COLS << ".\n";
        goto chooseNumberAgain;
    } catch (Input::fullColumn e) {
        std::cout << "Jogada Inválida.\n"
                     "Você tentou jogar numa coluna cheia!\n"
                     "Escolha outra coluna.\n";
        goto chooseNumberAgain;
    }
}
