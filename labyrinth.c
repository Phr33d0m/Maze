/* Labyrinth Solver by D.M. (dm@politeia.in)
 * A fork from the Paul Griffiths code. Thanks!
 * ********************************************
 * Codigo en C para la resolucion de un laberinto.
 * 
 * Date: 02-07-2012
 */


#include "labyrinth.h"

int ImportLabyrinth(char *fn, struct labyrinth *labyrinth) {
    char buffer[BIGBUFFER];
    FILE *fp;
    char **map;
    int n = 0, rows=0, columns=0;

    // Abrir archivo
    if ( !(fp = fopen(fn, "r")) ) {
        puts("\nError al abrir el archivo.");
        perror(buffer);
        
        return 0;
    }

    fgets(buffer, BIGBUFFER, fp);
    sscanf(buffer, "%d %d", &rows, &columns);
    n = rows;

    if ( !(map = malloc(n * sizeof *map)) ) {
        fputs("Couldn't allocate memory for map\n", stderr);
        
        return 0;
    }

    n = 0;

    int x;
    for(x=0; x<rows; x++) {
        int i;
        fgets(buffer, columns+2, fp);

        if ( !(map[n] = malloc((strlen(buffer)+1) * sizeof map[n])) ) {
            puts("\nNo se ha podido reservar memoria");

            for ( i = 0; i < n; ++i )
                free(map[i]);

            free(map);

            return 0;
        }
        strcpy(map[n], buffer);

        for ( i = strlen(map[n]) - 1; isspace(map[n][i]); --i ) {
            map[n][i] = 0;
        }

        ++n;
    }
    
    // Rellenar datos
    labyrinth->map = map;
    labyrinth->rows = rows;
    labyrinth->columns = columns;


    // Cerrar archivo
    if ( fclose(fp) ) {
        puts("Error al cerrar el archivo.");
        FreeMemory(labyrinth);
        
        return 0;
    }
    
    return 1;
}

void ShowLabyrinth(struct labyrinth *labyrinth) {
    int n;

    for ( n = 0; n < labyrinth->rows; ++n )
        puts(labyrinth->map[n]);
}

void FreeMemory(struct labyrinth *labyrinth) {
    int n;

    for ( n = 0; n < labyrinth->rows; ++n )
        free(labyrinth->map[n]);

    free(labyrinth->map);
}