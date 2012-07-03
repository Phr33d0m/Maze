/* Labyrinth Solver by D.M. (dm@politeia.in)
 * A fork from the Paul Griffiths code. Thanks!
 * ********************************************
 * Codigo en C para la resolucion de un laberinto.
 * Menú en Español.
 * 
 * Date: 02-07-2012
 */


#ifndef LABYRINTH_H
#define	LABYRINTH_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h> // Porque utilizaremos variables booleanas

// <<Etructuras>>
// --------------

// Estructura de nuestro laberinto
struct labyrinth {
    char **map;
    int beginx, beginy; // Coordenadas de la entrada
    int endx, endy; // Coordenadas de la salida
    int rows, columns; // Filas y columnas
    int startdir; // Direccion en la que empezar a resolver
};

// Estructura auxiliar con la que recorreremos el laberinto
struct position {
    int x, y, dir;
};



// <<Macros que utilizara el programa>>
// ------------------------------------

// Estos macros de aqui abajo se pueden cambiar dependiendo del sistema operativo
// y condiciones del laberinto.
#define CLEAR "clear"

#define BIGBUFFER (1000)

#define LABYRINTH_IN       'I'
#define LABYRINTH_OUT      'O'
#define LABYRINTH_WALL     'X'
#define LABYRINTH_PATH     ' '
#define LABYRINTH_TRACE    'o'
#define LABYRINTH_VISITED  ' '

// De aqui hacia abajo no es recomendable cambiar nada!
#define MOVE_LEFT  (3)
#define MOVE_UP    (2)
#define MOVE_RIGHT (1)
#define MOVE_DOWN  (0)

#define MOVE_LEFT_OP  (0)
#define MOVE_UP_OP    (1)
#define MOVE_RIGHT_OP (2)
#define MOVE_DOWN_OP  (3)

#define LABYRINTH_NOWAY      (0)
#define LABYRINTH_FOUNDEXIT  (1)
#define LABYRINTH_NOEXIT    (-1)

#define CONTINUE        "\nPulse intro (Enter) para continuar..."


// <<Declaracion de funciones>>
// ----------------------------

// Funcion para importar el laberinto desde un archivo
int ImportLabyrinth(char *fn, struct labyrinth *labyrinth);

// Mostrar el laberinto
void ShowLabyrinth(struct labyrinth *labyrinth);

// Liberar memoria, 'destruye' el laberinto.
void FreeMemory(struct labyrinth *labyrinth);



#endif	/* LABYRINTH_H */

