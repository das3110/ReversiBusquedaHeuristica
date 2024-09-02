#include "board.hpp"
#include <iostream>

Board::Board() {
    board.resize(8, std::vector<MARK>(8, EMPTY));
    board[3][3] = WHITE;
    board[4][4] = WHITE;
    board[3][4] = BLACK;
    board[4][3] = BLACK;
    turn = BLACK;
}

Board::~Board() = default;

bool Board::isLegalMove(int row, int col) {
    //logica para verificarmov legales
    if (board[row][col] != EMPTY)
        return false;
    //verificar direcciones
    return true;
}

bool Board::makeMove(int row, int col) {
    if (isLegalMove(row, col)) {
        board[row][col] = turn;
        //girar fichas
        turn = (turn == BLACK) ? WHITE : BLACK;
        return true;
    }
    return false;
}

void Board::print() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            char c = (board[i][j] == BLACK) ? 'B' : (board[i][j] == WHITE) ? 'W' : '-';
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool Board::hasLegalMoves(MARK player) {
    //verificación de movimientos legales
    return true;
}

MARK Board::getWinner() {
    //logica para determinar el ganador
    return EMPTY;
}
