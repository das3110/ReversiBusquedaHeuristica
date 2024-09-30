PROYECTO REVERSI

DESCRIPCIÓN

Reversi es un juego de estrategia para dos jugadores que se juega en un tablero cuadrado de 8x8.
Cada jugador tiene piezas de un color (blanco o negro) 
y el objetivo es tener más piezas de tu color en el tablero al final de la partida. 
Este proyecto implementa el juego en C++ y permite jugar contra un oponente aleatorio.

REQUISITOS

Antes de compilar el proyecto, asegúrate de tener instalado lo siguiente:

- C++ Compiler (g++ recomendado)
- CMake (versión 3.10 o superior)
- Ubuntu 20.04 (o compatible)

COMPILACIÓN

Sigue estos pasos para compilar el proyecto:

1. Crea un directorio de construcción:
   mkdir build
   cd build

2. Ejecuta CMake para configurar el proyecto:
   cmake ..

3. Compila el proyecto:
   make

4. Ejecuta el juego:
   ./Reversi

USO

Una vez que el juego esté en funcionamiento, 
se te pedirá que introduzcas tus movimientos en formato `fila columna` (por ejemplo, `3 2`). 
Para salir del juego, introduce `-1`.
