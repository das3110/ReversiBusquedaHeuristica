#include <iostream>
#include "board.hpp"
#include "random_player.hpp"
#include <string>
#include <limits> // Para std::numeric_limits

void getPlayerMove(int &row, int &col) {
    std::string input;

    while (true) {
        std::cout << "Introduce tu movimiento (fila columna) o -1 para salir: ";
        std::getline(std::cin, input);

        // Comprobar si el usuario quiere salir
        if (input == "-1") {
            row = -1; // Se puede establecer el valor de salida que desees
            col = -1;
            return;
        }

        // Comprobar si la entrada tiene 2 caracteres
        if (input.length() != 3 || input[1] != ' ') {
            std::cout << "Entrada inválida. Por favor, introduce dos números separados por un espacio." << std::endl;
            continue;
        }

        // Verificar que ambos caracteres son dígitos
        if (!isdigit(input[0]) || !isdigit(input[2])) {
            std::cout << "Entrada inválida. Por favor, introduce solo números." << std::endl;
            continue;
        }

        // Convertir caracteres a enteros
        row = input[0] - '0'; // Convierte el caracter a entero
        col = input[2] - '0'; // Convierte el caracter a entero

        // Comprobar si las posiciones están dentro del rango permitido
        if (row < 0 || row > 7 || col < 0 || col > 7) {
            std::cout << "Posición fuera de límites. Por favor, introduce valores entre 0 y 7." << std::endl;
            continue;
        }

        // Si todas las comprobaciones son exitosas, sal del bucle
        break;
    }
}

int main() {
    Board board;
    RandomPlayer ai(MARK::WHITE); 
    MARK playerColor = MARK::BLACK; 

    board.printBoard();

    while (true) {
        int row, col;

        // Turno del jugador
        std::cout << "Es tu turno. Tu color es " << (playerColor == MARK::BLACK ? "NEGRO" : "BLANCO") << "." << std::endl;

        // Obtener el movimiento del jugador
        getPlayerMove(row, col);
        
        // Verificar si el jugador quiere salir
        if (row == -1 && col == -1) {
            std::cout << "Saliendo del juego..." << std::endl;
            break;
        }

        if (board.makeMove(row, col, playerColor)) {
            board.printBoard();
        } else {
            std::cout << "Movimiento inválido. Inténtalo de nuevo." << std::endl;
            continue; // Permitir al jugador intentar nuevamente
        }

        // Comprobar si hay movimientos válidos para la IA
        if (!board.hasValidMoves(MARK::WHITE)) {
            std::cout << "La IA no tiene movimientos válidos. Tu turno nuevamente." << std::endl;
            continue; // Volver al turno del jugador
        }

        // Movimiento de la IA
        uint64_t aiMove = ai.makeMove(board, MARK::WHITE);
        row = static_cast<int>(aiMove >> 32); 
        col = static_cast<int>(aiMove & 0xFFFFFFFF); 

        if (board.makeMove(row, col, MARK::WHITE)) {
            board.printBoard();
        } else {
            std::cout << "La IA hizo un movimiento inválido. Esto no debería pasar." << std::endl;
        }

        // Comprobar si hay movimientos válidos para el jugador
        if (!board.hasValidMoves(MARK::BLACK)) {
            std::cout << "No tienes más movimientos válidos. Fin del juego." << std::endl;
            break; // Termina el juego si el jugador no puede moverse
        }
    }

    // Contar las piezas y determinar el ganador
    int blackCount = board.countPieces(MARK::BLACK);
    int whiteCount = board.countPieces(MARK::WHITE);
    if (blackCount > whiteCount) {
        std::cout << "¡NEGRO gana!" << std::endl;
    } else if (whiteCount > blackCount) {
        std::cout << "¡BLANCO gana!" << std::endl;
    } else {
        std::cout << "¡Es un empate!" << std::endl;
    }

    return 0;
}
