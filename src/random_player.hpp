#ifndef RANDOM_PLAYER_HPP
#define RANDOM_PLAYER_HPP

#include "board.hpp"
#include <chrono>
#include <vector>  // Añadir la inclusión para el uso de std::vector

// Estructura para almacenar las estadísticas de profundidad
struct DepthStat {
    int depth;          // Profundidad actual
    double time;        // Tiempo de búsqueda en milisegundos
    int nodes;          // Número de nodos evaluados
    double successRate; // Tasa de éxito en porcentaje
};

class RandomPlayer {
public:
    RandomPlayer(MARK player);
    uint64_t makeMove(const Board& board, MARK player);
    void resetStats();
    void printStats() const;

private:
    MARK player;
    int nodesVisited;    // Contador de nodos visitados
    double totalTime;    // Tiempo total de búsqueda

    std::vector<DepthStat> depthStatistics;  // Vector para almacenar estadísticas de cada profundidad

    int negamax(Board board, int depth, int alpha, int beta, MARK currentPlayer);
    int evaluate(const Board& board, MARK player);
    bool hasValidMoves(const Board& board, MARK player);
};

#endif // RANDOM_PLAYER_HPP
