/* Labyrinth Solver by D.M. (dm@politeia.in)
 * A fork from the Paul Griffiths code. Thanks!
 * Menu in English.
 * ********************************************
 * Codigo en C para la resolucion de un laberinto. 
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

// <<Structures>>
// --------------

// The structure of the maze
struct labyrinth {
    char **map;
    int beginx, beginy; // Entrance coordinates
    int endx, endy; // Exit coordinates
    int rows, columns; // Rows and columns
    int startdir; // Starting direction in which we'll start searching [0-3]
};

// Auxiliar structure with which we'll browse the maze
struct position {
    int x, y, dir;
};



// <<Macros>>
// ----------

// Please change this macros corresponding to your operating system and maze conditions
// Note: CLEAR for Linux is "clear" and for Windows is "cls"
#define CLEAR "clear"

#define BIGBUFFER (1000)

#define LABYRINTH_IN       'I'
#define LABYRINTH_OUT      'O'
#define LABYRINTH_WALL     'X'
#define LABYRINTH_PATH     ' '
#define LABYRINTH_TRACE    'o'
#define LABYRINTH_VISITED  ' '

// Don't change anything below if you don't know what you're doing.
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

#define CONTINUE        "\nPress Enter to continue..."


// <<Declaration of functions>>
// ----------------------------

// Function to import the maze from a file
int ImportLabyrinth(char *fn, struct labyrinth *labyrinth);

// Print the maze
void ShowLabyrinth(struct labyrinth *labyrinth);

// This will free the memory used by the maze.
void FreeMemory(struct labyrinth *labyrinth);



#endif	/* LABYRINTH_H */

