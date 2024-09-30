#include "random_player.hpp"
#include <iostream>
#include <vector>
#include <limits>
#include <random>
#include <chrono>


RandomPlayer::RandomPlayer(MARK player) 
    : player(player), nodesVisited(0), totalTime(0) {
    // Inicializar depthStatistics con un tamaño adecuado, si es necesario
    depthStatistics.resize(8); // Si se van a calcular hasta profundidad 6
    for (int i = 0; i < 8; ++i) {
        depthStatistics[i].depth = i + 1; // 1 a 6
        depthStatistics[i].time = 0;
        depthStatistics[i].nodes = 0;
        depthStatistics[i].successRate = 0;
    }
}

void RandomPlayer::resetStats() {
    nodesVisited = 0;
    totalTime = 0;
    // Reiniciar depthStatistics
    for (auto& stat : depthStatistics) {
        stat.nodes = 0;
        stat.time = 0;
        stat.successRate = 0;
    }
}

double calculateSuccessRate(int improvedMoves, int totalMoves) {
    if (totalMoves == 0) return 0.0; // Evitar división por cero
    return (static_cast<double>(improvedMoves) / totalMoves) * 100.0; // Retorna el porcentaje de movimientos que mejoraron
}


void RandomPlayer::printStats() const {
    std::cout << "=== Estadísticas del Jugador Aleatorio ===" << std::endl;
    std::cout << "Nodos revisados: " << nodesVisited << std::endl;
    std::cout << "Tiempo total (s): " << totalTime << std::endl;

    if (totalTime > 0) {
        std::cout << "Nodos por segundo: " << nodesVisited / totalTime << std::endl;
    }

    std::cout << "=== Estadísticas por Nivel de Profundidad ===" << std::endl;
    std::cout << "| Profundidad | Tiempo de Búsqueda (ms) | Nodos Evaluados " << std::endl;
    std::cout << "|-------------|-------------------------|------------------" << std::endl;

    for (const auto& depthStat : depthStatistics) { // depthStatistics es un vector que almacena la info por nivel de profundidad
        std::cout << "| " << depthStat.depth << "          | " 
                  << depthStat.time << "                  | " 
                  << depthStat.nodes << "            | " << std::endl;
    }

    std::cout << "==========================================" << std::endl;
}

uint64_t RandomPlayer::makeMove(const Board& board, MARK player) {
    resetStats(); // Resetea las estadísticas al iniciar un nuevo movimiento
    auto start = std::chrono::high_resolution_clock::now();

    int bestScore = std::numeric_limits<int>::min();
    uint64_t bestMove = 0;

    // Aplicar iterative deepening
    for (int depth = 1; depth <= 8; ++depth) { // Cambia 8 a cualquier límite que desees
        int successfulMoves = 0; // Contar movimientos exitosos en este nivel
        int totalMoves = 0; // Contar el total de movimientos posibles
        auto depthStart = std::chrono::high_resolution_clock::now();

        // Evaluar el estado inicial del tablero antes de realizar movimientos
        int previousScore = evaluate(board, player); // Evaluar antes del movimiento

        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                if (board.canMakeMove(row, col, player)) {
                    Board newBoard = board;
                    newBoard.makeMove(row, col, player);

                    // Evaluar el estado del tablero después de hacer el movimiento
                    int newScore = evaluate(newBoard, player); // Evaluar después del movimiento

                    // Comparar la puntuación antes y después
                    if (newScore > previousScore) {
                        successfulMoves++; // Contar como movimiento exitoso si el nuevo estado mejora
                    }
                    totalMoves++; // Aumentar el total de movimientos posibles

                    // Ejecutar el Negamax para decidir el mejor movimiento
                    int score = -negamax(newBoard, depth - 1, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), player);
                    if (score > bestScore) {
                        bestScore = score;
                        bestMove = (static_cast<uint64_t>(row) << 32) | col; // Guardar movimiento
                    }
                }
            }
        }

        auto depthEnd = std::chrono::high_resolution_clock::now();
        depthStatistics[depth - 1].time = std::chrono::duration<double, std::milli>(depthEnd - depthStart).count();
        depthStatistics[depth - 1].nodes = nodesVisited; // Total de nodos evaluados
        depthStatistics[depth - 1].successRate = calculateSuccessRate(successfulMoves, totalMoves); // Calcular la tasa de éxito

        //nodesVisited = 0; // Reiniciar el contador de nodos para el siguiente nivel de profundidad
    }

    auto end = std::chrono::high_resolution_clock::now();
    totalTime += std::chrono::duration<double>(end - start).count();
    // Supongamos que tienes 'nodesVisited' y 'totalTime' (en milisegundos).
    double nodesPorSegundo = 0;
    if (totalTime > 0) {
        nodesPorSegundo = nodesVisited / (totalTime / 1000.0);  // Dividir por 1000 para convertir ms a segundos
    }

    printStats(); // Imprime estadísticas después de hacer el movimiento
    return bestMove;
}


int RandomPlayer::negamax(Board board, int depth, int alpha, int beta, MARK currentPlayer) {
    nodesVisited++; // Contar nodos revisados

    if (depth == 0 || !hasValidMoves(board, currentPlayer)) {
        return evaluate(board, currentPlayer); // Lógica de evaluación
    }

    int bestValue = std::numeric_limits<int>::min();

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (board.canMakeMove(row, col, currentPlayer)) {
                Board newBoard = board;
                newBoard.makeMove(row, col, currentPlayer);
                int score = -negamax(newBoard, depth - 1, -beta, -alpha, (currentPlayer == MARK::BLACK) ? MARK::WHITE : MARK::BLACK);
                bestValue = std::max(bestValue, score);
                alpha = std::max(alpha, score);
                if (beta <= alpha) {
                    break; // Poda
                }
            }
        }
    }
    return bestValue;
}

int RandomPlayer::evaluate(const Board& board, MARK player) {
    int score = board.countPieces(player) - board.countPieces((player == MARK::BLACK) ? MARK::WHITE : MARK::BLACK);

    // Valor por esquinas
    int cornerValue = 0;
    if (board.isCornerOccupied(player)) cornerValue += 5;
    if (board.isCornerOccupied((player == MARK::BLACK) ? MARK::WHITE : MARK::BLACK)) cornerValue -= 5;

    return score + cornerValue;
}

bool RandomPlayer::hasValidMoves(const Board& board, MARK player) {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (board.canMakeMove(row, col, player)) {
                return true;
            }
        }
    }
    return false;
}
