/* Labyrinth Solver by D.M. (dm@politeia.in)
 * A fork from the Paul Griffiths code. Thanks!
 * ********************************************
 * Codigo en C para la resolucion de un laberinto.
 * Menú en Español.
 * 
 * Date: 02-07-2012
 */


#include "solver.h"

int solve(struct labyrinth *labyrinth, bool opt) {
    struct position position;

    // Ahora toca decidir en que direccion empezaremos.
    if ( labyrinth->beginx < strlen(labyrinth->map[labyrinth->beginy]) - 1 && labyrinth->map[labyrinth->beginy][labyrinth->beginx+1] != LABYRINTH_WALL ) {
        if(opt) labyrinth->startdir = MOVE_RIGHT_OP;
        else labyrinth->startdir = MOVE_RIGHT;
    }
    else if ( labyrinth->beginx > 0 && labyrinth->map[labyrinth->beginy][labyrinth->beginx-1] != LABYRINTH_WALL ) {
        if(opt) labyrinth->startdir = MOVE_LEFT_OP;
        else labyrinth->startdir = MOVE_LEFT;
    }
    else if ( labyrinth->beginy > 0 && labyrinth->map[labyrinth->beginy-1][labyrinth->beginx] != LABYRINTH_WALL ) {
        if(opt) labyrinth->startdir = MOVE_UP_OP;
        else labyrinth->startdir = MOVE_UP;
    }
    else if ( labyrinth->beginy < (labyrinth->rows-1) && labyrinth->map[labyrinth->beginy+1][labyrinth->beginx] != LABYRINTH_WALL ) {
        if(opt) labyrinth->startdir = MOVE_DOWN_OP;
        else labyrinth->startdir = MOVE_DOWN;
    }
    
    // Nos posicionamos
    position.x = labyrinth->beginx;
    position.y = labyrinth->beginy;
    position.dir = labyrinth->startdir;
    
    return resolve(labyrinth, position, opt);
} 



int resolve(struct labyrinth *labyrinth, struct position position, bool opt) {
    int i, n;

    // Este if() depende de si queremos la solucion optima o una cualquiera
    if(opt) {
        switch ( position.dir ) {
            case MOVE_UP_OP:
                position.y -= 1;
                break;

            case MOVE_DOWN_OP:
                position.y += 1;
                break;

            case MOVE_LEFT_OP:
                position.x -= 1;
                break;

            case MOVE_RIGHT_OP:
                position.x += 1;
                break;

            default:
                break;
        }
    }
    else {
        switch ( position.dir ) {
            case MOVE_UP:
                position.y -= 1;
                break;

            case MOVE_DOWN:
                position.y += 1;
                break;

            case MOVE_LEFT:
                position.x -= 1;
                break;

            case MOVE_RIGHT:
                position.x += 1;
                break;

            default:
                break;
        }
    }

    if ( position.y < 0 || position.y >= labyrinth->rows )
        return LABYRINTH_NOWAY;
    else if ( position.x < 0 || position.x >= strlen(labyrinth->map[position.y]) )
        return LABYRINTH_NOWAY;
    else if ( labyrinth->map[position.y][position.x] == LABYRINTH_WALL || labyrinth->map[position.y][position.x] == LABYRINTH_TRACE )
        return LABYRINTH_NOWAY;
    else if ( labyrinth->map[position.y][position.x] == LABYRINTH_OUT )
        return LABYRINTH_FOUNDEXIT;
    else if ( labyrinth->map[position.y][position.x] == LABYRINTH_IN )
        return LABYRINTH_NOEXIT;

    position.dir -= 1;
    if ( position.dir < 0 )
        position.dir += 4;
    
    for ( i = 0; i < 3; ++i ) {
        labyrinth->map[position.y][position.x] = LABYRINTH_TRACE; 
        
        n = resolve(labyrinth, position, opt);
        if (n) {
            if (n == LABYRINTH_NOEXIT) {
                labyrinth->map[position.y][position.x] = LABYRINTH_VISITED;
            }
            return n;
        }

        position.dir += 1;
        if ( position.dir > 3 )
            position.dir -= 4;
    }

    labyrinth->map[position.y][position.x] = LABYRINTH_VISITED;
    return 0;
}

