#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <cstdint>

enum class MARK { EMPTY, BLACK, WHITE };

class Board {
public:
    Board();
    void printBoard() const;
    bool makeMove(int row, int col, MARK player);
    uint64_t flipPieces(int row, int col, MARK player); // Sin const
    bool canMakeMove(int row, int col, MARK player) const;
    bool hasValidMoves(MARK player) const;
    int countPieces(MARK player) const;
    uint64_t getBoard() const;
    bool isCornerOccupied(MARK player) const;

private:
    std::array<std::array<MARK, 8>, 8> grid;
};

#endif // BOARD_HPP
