#include "board.hpp"
#include <iostream>

int main() {
    Board board;
    board.print();

    int row, col;
    while (board.hasLegalMoves(BLACK) || board.hasLegalMoves(WHITE)) {
        std::cout << "Ingrese fila y columna (0-7) para hacer un movimiento: ";
        std::cin >> row >> col;

        if (!board.makeMove(row, col)) {
            std::cout << "Movimiento ilegal. Intente de nuevo." << std::endl;
        }

        board.print();
    }

    MARK winner = board.getWinner();
    if (winner == BLACK) {
        std::cout << "Negro ha ganado" << std::endl;
    } else if (winner == WHITE) {
        std::cout << "Blanco ha ganado" << std::endl;
    } else {
        std::cout << "Empate" << std::endl;
    }

    return 0;
}
