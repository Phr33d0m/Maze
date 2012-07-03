/* Labyrinth Solver by D.M. (dm@politeia.in)
 * A fork from the Paul Griffiths code. Thanks!
 * Menu in English.
 * ********************************************
 * Codigo en C para la resolucion de un laberinto. 
 * 
 * Date: 02-07-2012
 */


#ifndef SOLVER_H
#define	SOLVER_H

#include "labyrinth.h"

// Functions that will solve the maze.
int solve(struct labyrinth *labyrinth, bool opt);
int resolve(struct labyrinth *labyrinth, struct position position, bool opt);


#endif	/* SOLVER_H */

