#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define ZELVICKY_MAX_COUNT 3

enum Smery {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
};

struct Vector2 {
    int x;
    int y;
};

struct Zelva {
    struct Vector2 location;
    enum Smery smer;
    bool active;
};

//canvas
void setupCanvas(char*** canvas, int *rows, int *columns);
void printCanvas(char*** canvas, const int *rows, const int *columns);
void printCanvasWithTurtles(char*** canvas, const int *rows, const int *columns, const struct Zelva *zelvy);
void nullOutCanvas(char*** canvas, const int *rows, const int *columns);


//zelva
void zelvaSetup(struct Zelva *zelva);
void changeDirection(struct Zelva *zelva, enum Smery novySmer);
void move(struct Zelva *zelva, struct Vector2 canvasSize);
void udelejKolecko(struct Vector2 location, char ***canvas);





int main() {
    char **canvas;

    struct Vector2 canvasSize;


    setupCanvas(&canvas, &canvasSize.y, &canvasSize.x);

    nullOutCanvas(&canvas, &canvasSize.y, &canvasSize.x);

    struct Zelva zelvicky[ZELVICKY_MAX_COUNT];

    for (int i = 0; i < ZELVICKY_MAX_COUNT; ++i) {
        zelvicky[i].active = false;
    }

    zelvaSetup(&zelvicky[0]);

    char prikaz;

    while (1) {
        scanf(" %c", &prikaz);
        switch (prikaz) {
            case 'r':{
                for (int i = 0; i < ZELVICKY_MAX_COUNT; ++i) {
                    if (zelvicky[i].active == true) {
                        changeDirection(&zelvicky[i],(zelvicky[i].smer + 1) % 4);
                    }
                }
            }break;
            case 'l':{
                for (int i = 0; i < ZELVICKY_MAX_COUNT; ++i) {
                    if (zelvicky[i].active == true) {
                        changeDirection(&zelvicky[i],(zelvicky[i].smer + 3) % 4);
                    }
                }
            }break;
            case 'm':{
                for (int i = 0; i < ZELVICKY_MAX_COUNT; ++i) {
                    if (zelvicky[i].active == true) {
                        move(&zelvicky[i], canvasSize);
                    }
                }
            }break;
            case 'o':{
                for (int i = 0; i < ZELVICKY_MAX_COUNT; ++i) {
                    if (zelvicky[i].active == true) {
                        udelejKolecko(zelvicky[i].location, &canvas);
                    }
                }
            }break;
            case 'f':{
                for (int i = 0; i < ZELVICKY_MAX_COUNT; ++i) {
                    if (zelvicky[i].active == false) {
                        zelvaSetup(&zelvicky[i]);
                        break;
                    }
                }
            }break;
            case 'x': {
                printCanvas(&canvas, &canvasSize.y, &canvasSize.x);
                for (int i = 0; i < canvasSize.y; i++) {
                    free(canvas[i]);
                }
                free(canvas);
                return 0;
            }
        }
        // printCanvas(&canvas, &canvasSize.y, &canvasSize.x);
    }
}


//canvas
void setupCanvas(char*** canvas, int *rows, int *columns) {

    scanf("%d", rows);
    scanf("%d", columns);


    *canvas = malloc(sizeof(char*) * (*rows));
    for (int i = 0; i < *rows; i++) {
        (*canvas)[i] = malloc(sizeof(char) * (*columns));
    }

}

void nullOutCanvas(char*** canvas, const int *rows, int const *columns) {
    for (int i = 0; i < *rows; ++i) {
        for (int j = 0; j < *columns; ++j) {
            (*canvas)[i][j] = '.';
        }
    }
}

void printCanvas(char*** canvas, const int *rows, const int *columns) {
    // printf("loc %d %d\n", zelva.location.x, zelva.location.y);
    // printf("dir %d\n", zelva.smer);
    for (int i = 0; i < *rows; ++i) {
        for (int j = 0; j < *columns; ++j) {
            // if (zelva.location.x == j && zelva.location.y == i) {
            //     printf("@");
            // }
            // else {
                printf("%c", (*canvas)[i][j]);
            // }
        }
        printf("\n");
    }
}
void printCanvasWithTurtles(char*** canvas, const int *rows, const int *columns, const struct Zelva *zelvy) {
    // printf("loc %d %d\n", zelva.location.x, zelva.location.y);
    // printf("dir %d\n", zelva.smer);

    for (int i = 0; i < *rows; ++i) {
        for (int j = 0; j < *columns; ++j) {
            bool turtlePrinted = false;
            for (int k = 0; k < ZELVICKY_MAX_COUNT; ++k) {
                if (zelvy[k].active) {
                    if (zelvy[k].location.x == j && zelvy[k].location.y == i) {
                        printf("z");
                        turtlePrinted = true;
                        break;
                    }
                }
            }
            if (!turtlePrinted) {
                printf("%c", (*canvas)[i][j]);
            }
        }
        printf("\n");
    }
}





//zelva

void zelvaSetup(struct Zelva *zelva){

    struct Vector2 startLocation = {0,0};
    zelva->location = startLocation;

    zelva->smer = EAST;

    zelva->active = true;

}

void changeDirection(struct Zelva *zelva, enum Smery novySmer) {
    zelva->smer = novySmer;
}

void move(struct Zelva *zelva, const struct Vector2 canvasSize) {

    struct Vector2 newLocation =
        {zelva->location.x += (zelva->smer == EAST)?1:(zelva->smer == WEST)?-1:0,
        zelva->location.y += (zelva->smer == SOUTH)?1:(zelva->smer == NORTH)?-1:0};

    //printf("Location x: %d  y: %d\n", newLocation.x,newLocation.y);

    if (newLocation.x < 0) {
        newLocation.x = canvasSize.x - 1;
    }else if (newLocation.x >= canvasSize.x) {
        newLocation.x = 0;
    }
    if (newLocation.y < 0) {
        newLocation.y = canvasSize.y - 1;
    }else if (newLocation.y >= canvasSize.y) {
        newLocation.y = 0;
    }

    //printf("Changed Location x: %d  y: %d\n", newLocation.x,newLocation.y);

    zelva->location = newLocation;
}

void udelejKolecko(struct Vector2 location, char ***canvas) {
    if ((*canvas)[location.y][location.x] == '.') {
        (*canvas)[location.y][location.x] ='o';
    }
    else if ((*canvas)[location.y][location.x] == 'o') {
        (*canvas)[location.y][location.x] ='.';
    }
}

void addBlocks(int n, char ***canvas, struct Vector2 *canvasSize);
void move2(struct Zelva *zelva, char ***canvas, const struct Vector2 *canvasSize);

// BONUSOVA ULOHA 1 (GENEROVANI MRIZEK)
/*
int main() {

    char **canvas;

    struct Vector2 canvasSize;

    setupCanvas(&canvas, &canvasSize.y, &canvasSize.x);

    nullOutCanvas(&canvas, &canvasSize.y, &canvasSize.x);

    struct Zelva zelvicky[ZELVICKY_MAX_COUNT];

    for (int i = 0; i < ZELVICKY_MAX_COUNT; ++i) {
        zelvicky[i].active = false;
    }

    zelvaSetup(&zelvicky[0]);

    addBlocks(5,&canvas, &canvasSize);

    printCanvas(&canvas,&canvasSize.y,&canvasSize.x);
    char prikaz;

    while (1) {
        scanf(" %c", &prikaz);
        switch (prikaz) {
            case 'r':{
                for (int i = 0; i < ZELVICKY_MAX_COUNT; ++i) {
                    if (zelvicky[i].active == true) {
                        changeDirection(&zelvicky[i],(zelvicky[i].smer + 1) % 4);
                    }
                }
            }break;
            case 'l':{
                for (int i = 0; i < ZELVICKY_MAX_COUNT; ++i) {
                    if (zelvicky[i].active == true) {
                        changeDirection(&zelvicky[i],(zelvicky[i].smer + 3) % 4);
                    }
                }
            }break;
            case 'm':{
                for (int i = 0; i < ZELVICKY_MAX_COUNT; ++i) {
                    if (zelvicky[i].active == true) {
                        move2(&zelvicky[i], &canvas, &canvasSize);
                    }
                }
            }break;
            case 'o':{
                for (int i = 0; i < ZELVICKY_MAX_COUNT; ++i) {
                    if (zelvicky[i].active == true) {
                        udelejKolecko(zelvicky[i].location, &canvas);
                    }
                }
            }break;
            case 'f':{
                for (int i = 0; i < ZELVICKY_MAX_COUNT; ++i) {
                    if (zelvicky[i].active == false) {
                        zelvaSetup(&zelvicky[i]);
                        break;
                    }
                }
            }break;
            case 'x': {
                printCanvas(&canvas, &canvasSize.y, &canvasSize.x);
                for (int i = 0; i < canvasSize.y; i++) {
                    free(canvas[i]);
                }
                free(canvas);
                return 0;
            }
        }
        printCanvasWithTurtles(&canvas, &canvasSize.y, &canvasSize.x, zelvicky);
    }

}
*/

void addBlocks(int n, char ***canvas, struct Vector2 *canvasSize) {
    for (int i = 0; i < n; ++i) {
        (*canvas)[rand()%canvasSize->y][rand() % canvasSize->x] = '#';
    }
}

void move2(struct Zelva *zelva, char ***canvas, const struct Vector2 *canvasSize) {
    struct Vector2 newLocation =
    {zelva->location.x + ((zelva->smer == EAST)?1:(zelva->smer == WEST)?-1:0),
    zelva->location.y + ((zelva->smer == SOUTH)?1:(zelva->smer == NORTH)?-1:0)};

    //printf("Location x: %d  y: %d\n", newLocation.x,newLocation.y);

    if (newLocation.x < 0 ) {
        newLocation.x = canvasSize->x - 1;
    }else if (newLocation.x >= canvasSize->x) {
        newLocation.x = 0;
    }
    if (newLocation.y < 0) {
        newLocation.y = canvasSize->y - 1;
    }else if (newLocation.y >= canvasSize->y) {
        newLocation.y = 0;
    }

    char ggg = (*canvas)[newLocation.y][newLocation.x] ;
    if (ggg == '#') {
        return;
    }

    //printf("Changed Location x: %d  y: %d\n", newLocation.x,newLocation.y);

    zelva->location = newLocation;
}


// animace
/*
int main() {

    char **canvas;

    struct Vector2 canvasSize;

    setupCanvas(&canvas, &canvasSize.y, &canvasSize.x);

    nullOutCanvas(&canvas, &canvasSize.y, &canvasSize.x);

    struct Zelva zelvicky[ZELVICKY_MAX_COUNT];

    for (int i = 0; i < ZELVICKY_MAX_COUNT; ++i) {
        zelvicky[i].active = false;
    }

    zelvaSetup(&zelvicky[0]);

    printCanvas(&canvas,&canvasSize.y,&canvasSize.x);
    char prikaz;

    while (1) {
        scanf(" %c", &prikaz);
        switch (prikaz) {
            case 'r':{
                for (int i = 0; i < ZELVICKY_MAX_COUNT; ++i) {
                    if (zelvicky[i].active == true) {
                        changeDirection(&zelvicky[i],(zelvicky[i].smer + 1) % 4);
                    }
                }
            }break;
            case 'l':{
                for (int i = 0; i < ZELVICKY_MAX_COUNT; ++i) {
                    if (zelvicky[i].active == true) {
                        changeDirection(&zelvicky[i],(zelvicky[i].smer + 3) % 4);
                    }
                }
            }break;
            case 'm':{
                for (int i = 0; i < ZELVICKY_MAX_COUNT; ++i) {
                    if (zelvicky[i].active == true) {
                        move(&zelvicky[i], canvasSize);
                    }
                }
            }break;
            case 'o':{
                for (int i = 0; i < ZELVICKY_MAX_COUNT; ++i) {
                    if (zelvicky[i].active == true) {
                        udelejKolecko(zelvicky[i].location, &canvas);
                    }
                }
            }break;
            case 'f':{
                for (int i = 0; i < ZELVICKY_MAX_COUNT; ++i) {
                    if (zelvicky[i].active == false) {
                        zelvaSetup(&zelvicky[i]);
                        break;
                    }
                }
            }break;
            case 'x': {
                printCanvas(&canvas, &canvasSize.y, &canvasSize.x);
                for (int i = 0; i < canvasSize.y; i++) {
                    free(canvas[i]);
                }
                free(canvas);
                return 0;
            }
        }
        printCanvasWithTurtles(&canvas, &canvasSize.y, &canvasSize.x, zelvicky);

        usleep(1000 * 50);

        fflush(stdout);
    }

}
*/