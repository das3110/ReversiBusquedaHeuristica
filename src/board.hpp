#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>

enum MARK { EMPTY, BLACK, WHITE };

class Board {
    std::vector<std::vector<MARK>> board;
    MARK turn;

    bool isLegalMove(int row, int col);
    bool checkDirection(int row, int col, int dRow, int dCol, MARK player);

public:
    Board();
    ~Board();

    void print();
    bool makeMove(int row, int col);
    bool hasLegalMoves(MARK player);
    MARK getWinner();
};

#endif 