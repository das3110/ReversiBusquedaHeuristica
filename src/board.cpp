#include "board.hpp"
#include <iostream>
#include <iomanip>
#include <vector>

Board::Board() {
    for (auto& row : grid) {
        row.fill(MARK::EMPTY);
    }
    grid[3][3] = MARK::WHITE;
    grid[3][4] = MARK::BLACK;
    grid[4][3] = MARK::BLACK;
    grid[4][4] = MARK::WHITE;
}

void Board::printBoard() const {
    std::cout << "  0 1 2 3 4 5 6 7\n";
    for (int i = 0; i < 8; ++i) {
        std::cout << i << " ";
        for (int j = 0; j < 8; ++j) {
            char symbol = ' ';
            if (grid[i][j] == MARK::BLACK) symbol = 'B';
            else if (grid[i][j] == MARK::WHITE) symbol = 'W';
            std::cout << symbol << " ";
        }
        std::cout << "\n";
    }
}

bool Board::makeMove(int row, int col, MARK player) {
    if (!canMakeMove(row, col, player)) {
        return false;
    }
    grid[row][col] = player;
    flipPieces(row, col, player);
    return true;
}

uint64_t Board::flipPieces(int row, int col, MARK player) {
    static const std::vector<std::pair<int, int>> directions = {
        {-1, -1}, {-1, 0}, {-1, 1}, 
        {0, -1},           {0, 1}, 
        {1, -1}, {1, 0}, {1, 1}
    };

    uint64_t flipped = 0;

    for (const auto& direction : directions) {
        int r = row + direction.first;
        int c = col + direction.second;
        bool hasOpponent = false;

        // Primero, verificar si hay fichas oponentes en la dirección
        while (r >= 0 && r < 8 && c >= 0 && c < 8 && grid[r][c] != MARK::EMPTY) {
            if (grid[r][c] == player) {
                hasOpponent = true; // Se encontró una ficha del jugador
                break;
            }
            r += direction.first;
            c += direction.second;
        }

        // Si se encontró al menos una ficha del oponente y luego una del jugador
        if (hasOpponent) {
            r = row + direction.first;
            c = col + direction.second;
            // Voltear las fichas en esta dirección
            while (grid[r][c] != player) {
                grid[r][c] = player; 
                r += direction.first;
                c += direction.second;
            }
        }
    }

    return flipped; // Esta variable se puede usar para contar cuántas piezas se voltearon
}


bool Board::canMakeMove(int row, int col, MARK player) const {
    if (grid[row][col] != MARK::EMPTY) {
        return false; 
    }

    static const std::vector<std::pair<int, int>> directions = {
        {-1, -1}, {-1, 0}, {-1, 1}, 
        {0, -1},           {0, 1}, 
        {1, -1}, {1, 0}, {1, 1}
    };

    for (const auto& direction : directions) {
        int r = row + direction.first;
        int c = col + direction.second;
        bool hasOpponent = false;

        // Continuar mientras esté dentro del tablero
        while (r >= 0 && r < 8 && c >= 0 && c < 8) {
            if (grid[r][c] == MARK::EMPTY) {
                break; 
            }
            if (grid[r][c] == player) {
                // Si encontramos al menos un oponente y luego una ficha del jugador
                if (hasOpponent) {
                    return true; 
                } else {
                    break; 
                }
            }
            hasOpponent = true; 
            r += direction.first;
            c += direction.second;
        }
    }
    return false; 
}


bool Board::hasValidMoves(MARK player) const {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (canMakeMove(row, col, player)) {
                return true;
            }
        }
    }
    return false;
}

int Board::countPieces(MARK player) const {
    int count = 0;
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if (cell == player) {
                ++count;
            }
        }
    }
    return count;
}

uint64_t Board::getBoard() const {
    uint64_t boardState = 0; 
    return boardState;
}

bool Board::isCornerOccupied(MARK player) const {
    return (grid[0][0] == player || grid[0][7] == player || 
            grid[7][0] == player || grid[7][7] == player);
}
