/* Labyrinth Solver by D.M. (dm@politeia.in)
 * A fork from the Paul Griffiths code. Thanks!
 * Menu in English.
 * ********************************************
 * Codigo en C para la resolucion de un laberinto. 
 * 
 * Date: 02-07-2012
 */

// This library has everything we need, if you have to change anything go there
#include "labyrinth.h"

// Function to define input and output variables
// IOvars = Input Output variables
void IOvars(struct labyrinth *labyrinth, int *tempE, int *tempS, int *avance, bool redo);

// <<MAIN>>
// --------
int main() {
    // MENU vars
    int menu=-1, avance=0, tempE[1], tempS[1];
    char opcion[2];
    
    // Labyrinth vars
    struct labyrinth labyrinth;
    char file[1024];
    
    // === MENU ===
    // ------------
    do {
        menu=-1;
        
        system(CLEAR);
        puts("    ### LABYRINTH ###");
        puts("    #*#*#*#*#*#*#*#*#\n");
        puts(" 1.- Read the maze from a file.");
        puts(" 2.- Set the entrance and exit points.");
        puts(" 3.- Get a path.");
        puts(" 4.- Get the shortest path.");
        puts(" 5.- Exit.\n");
        printf(" >>: ");
        menu=atoi(gets(opcion));
        
        switch(menu){
            case 1: 
                system(CLEAR);
                puts("1.- Leer el laberinto."); 
                puts("**********************");
                printf("Introduzca nombre de archivo: ");
                gets(file);
                
                // Liberamos memoria si antes habiamos cargado otro laberinto.
                if(avance>0) FreeMemory(&labyrinth);
                
                if(ImportLabyrinth(file, &labyrinth)) {
                    avance=1;
                    puts("\nArchivo leido y laberinto importado con exito!");
                    printf("--- Filas: %d\n--- Columnas: %d\n",labyrinth.rows,labyrinth.columns);
                    ShowLabyrinth(&labyrinth);
                }
                else puts("Ha habido un error en la lectura del fichero");
                
                puts(CONTINUE);
                getchar();
                break;

            case 2: 
                system(CLEAR);
                puts("2.- Definir los puntos de entrada y salida."); 
                puts("*******************************************");
                
                if(avance>0) {
                    IOvars(&labyrinth, &tempE[0], &tempS[0], &avance, false);
                    printf("\navance='%d'\ntempE[0]='%d'\ntempE[1]='%d'\ntempS[0]='%d'\ntempS[1]='%d'\n",avance,tempE[0],tempE[1],tempS[0],tempS[1]);
                    puts(CONTINUE);
                    getchar();
                }
                else { 
                    puts("No puedes acceder aqui antes de cargar el laberinto.");
                    puts(CONTINUE);
                    getchar();
                }
                break;
                
            case 3: 
                system(CLEAR);
                puts("3.- Obtener un camino."); 
                puts("**********************");
                
                if(avance>1) {
                    if (solve(&labyrinth, false) == LABYRINTH_FOUNDEXIT) {
                        puts("\nSe ha encontrado una salida!");
                        ShowLabyrinth(&labyrinth);
                        
                        // Si, aunque me duela en el alma lo tendre que hacer...
                        FreeMemory(&labyrinth);
                        // Importar laberinto otra vez
                        ImportLabyrinth(file, &labyrinth);
                        // Importar coordenadas otra vez
                        IOvars(&labyrinth, &tempE[0], &tempS[0], &avance, true);
                    }
                    else {
                        puts("\n\nNo se ha encontrado ninguna salida!\nSi cree que esto es un error, por favor no suspenda al programador!!");
                    }
                    puts(CONTINUE);
                    getchar();
                }
                else { 
                    puts("No puedes acceder aqui antes de cargar el laberinto y definir las entradas/salidas.");
                    puts(CONTINUE);
                    getchar();
                }
                break;

            case 4: 
                system(CLEAR);
                puts("4.- Obtener el camino más corto."); 
                puts("********************************");
                
                if(avance>1) {
                    if (solve(&labyrinth, true) == LABYRINTH_FOUNDEXIT) {
                        puts("\nSe ha encontrado la salida optima!");
                        ShowLabyrinth(&labyrinth);
                        
                        // Si alguien sabe como mejorar el aspecto de esto que me lo mande por github o email
                        FreeMemory(&labyrinth);
                        // Importar laberinto otra vez
                        ImportLabyrinth(file, &labyrinth);
                        // Importar coordenadas otra vez
                        IOvars(&labyrinth, &tempE[0], &tempS[0], &avance, true);
                    }
                    else {
                        puts("\n\nNo se ha encontrado ninguna salida!\nSi cree que esto es un error, por favor no suspenda al programador!!");
                    }
                    puts(CONTINUE);
                    getchar();
                }
                else { 
                    puts("No puedes acceder aqui antes de cargar el laberinto y definir las entradas/salidas.");
                    puts(CONTINUE);
                    getchar();
                }
                break;

            case 5:
                system(CLEAR);
                menu=5;
                puts(" \n  ***  FIN DEL PROGRAMA  ***\n"); 
                break;

            default:
            puts("Opcion erronea. Por favor elija una opcion del menu."); 
            break;
            
        }
    } while (menu!=5);

    system(CLEAR);
    return EXIT_SUCCESS;
    
}


void IOvars(struct labyrinth *labyrinth, int *tempE, int *tempS, int *avance, bool redo) {
    bool yesno=false;
    char *temp, number[1024];
    if(!redo) {
        while(!yesno) {
            puts("--- Coordenadas de entrada:");
            printf("--- X: ");
            //
            tempE[0]=atoi(gets(number));
            printf("--- Y: ");
            //
            tempE[1]=atoi(gets(number));

            if(tempE[0]<=labyrinth->columns && tempE[1]<=labyrinth->rows) {
                printf("\nRecibidos:\n--- X: %d\n--- Y: %d\n",tempE[0],tempE[1]);

                printf("Es correcto? [y/n] ");
                if(getchar()=='y') yesno = true;
                getchar();
                if(yesno) {
                    labyrinth->beginx=tempE[0]-1;
                    labyrinth->beginy=tempE[1]-1;
                }
            }
            else {
                puts("\nERROR: Se ha excedido en alguna de las variables.");
                printf("El valor maximo que puede tomar X es %d y el que puede tomar Y es %d",labyrinth->columns,labyrinth->rows);
            }

        }
        temp=labyrinth->map[labyrinth->beginy];
        temp[labyrinth->beginx] = LABYRINTH_IN;
        labyrinth->map[labyrinth->beginy]=temp;
        yesno=false;

        while(!yesno) {
            puts("--- Coordenadas de salida:");
            printf("--- X: ");
            //
            tempS[0]=atoi(gets(number));
            printf("--- Y: ");
            //
            tempS[1]=atoi(gets(number));

            if(tempS[0]<=labyrinth->columns && tempS[1]<=labyrinth->rows) {
                printf("\nRecibidos:\n--- X: %d\n--- Y: %d\n",tempS[0],tempS[1]);

                printf("Es correcto? [y/n] ");
                if(getchar()=='y') yesno = true;
                getchar();
                if(yesno) {
                    labyrinth->endx=tempS[0]-1;
                    labyrinth->endy=tempS[1]-1;
                }
            }
            else {
                puts("\nERROR: Se ha excedido en alguna de las variables.");
                printf("El valor maximo que puede tomar X es %d y el que puede tomar Y es %d",labyrinth->columns,labyrinth->rows);
            }

        }
        temp=labyrinth->map[labyrinth->endy];
        temp[labyrinth->endx] = LABYRINTH_OUT;
        labyrinth->map[labyrinth->endy]=temp;
        yesno=false;
        *avance=2;

        puts("");
        ShowLabyrinth(labyrinth);
    }
    else {
        labyrinth->beginx=tempE[0]-1;
        labyrinth->beginy=tempE[1]-1;
        labyrinth->endx=tempS[0]-1;
        labyrinth->endy=tempS[1]-1;
        temp=labyrinth->map[labyrinth->beginy];
        temp[labyrinth->beginx] = LABYRINTH_IN;
        labyrinth->map[labyrinth->beginy]=temp;
        temp=labyrinth->map[labyrinth->endy];
        temp[labyrinth->endx] = LABYRINTH_OUT;
        labyrinth->map[labyrinth->endy]=temp;
    }
}