#include "drawing.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>


typedef struct {
    int x;
    int y;
} Vector2;

typedef enum {
    STAIR_UP,
    STAIR_DOWN
} StairType;

typedef struct {
    Vector2 position;
    Vector2 size;
} Object;

typedef struct {
    Vector2* body;
    const int length;
} Snake;


void pixel();
void pixelDebug();

void prerusovaneCary(Vector2 start, int length);
void schody(StairType stairType, int length);
void kvetina(int width, int height, int posX, int posY);
void louka(int columns, int rows);

void animace();
void moveSnakeRandom(Snake* snake);
void showSnake(Snake* snake);
void showSnakeBodyDebug(Snake* snake);
bool isPosInSnake(Snake* snake, Vector2 newPos);

int main() {

    clear_screen();

    int drawing = 0;
    scanf("%d", &drawing);
    clear_screen();

    switch (drawing) {
        case 0:{
            Vector2 startPos = {1,1};
            prerusovaneCary(startPos,2);

            Vector2 startPos2 = {4,8};
            prerusovaneCary(startPos2, 6);

            Vector2 startPos3 = {7,3};
            prerusovaneCary(startPos3, 3);

        }break;
        case 1:{
            schody(STAIR_DOWN, 20);

        }break;
        case 2:{
            kvetina(5,10,6,3);

        }break;
        case 3: {
            louka(4,2);


        }break;
        case 4: {
            animace();
        }break;
    }
    end_drawing();

    return 0;
}

void prerusovaneCary(Vector2 start, int length) {

    move_to(start.x, start.y);
    set_red_color();
    for (int i = 0; i < length*2; i++)
    {
        if (i % 2 != 0)
        {
            printf("  ");
            
        }

        move_right();
    }
    
}

void schody(StairType stairType, int length){
    switch (stairType)
    {
    case 0:{

    }break;
    case 1:{
        for (int i = 0; i < length; i++)
        {
            set_green_color();
            printf("  ");
            move_down();
        }
        

    }break;

    default:
        break;
        printf("stairType je spatne");
    }
}

void kvetina(int width, int height, int posX, int posY){ // 3, 8
    set_yellow_color();

    for (int i = 0; i < width; i++) // height
    {
        move_to(posY + i,posX*2);
        for (int j = 0; j < width; j++) // width
        {
            if(
                    (i == 0 && j == 0 ) ||
                    (i == 0 && j == width-1) ||
                    (i == width-1 && j == 0) ||
                    (i == width-1 && j == width-1)
                ){reset_color();}
            else{set_yellow_color();}

            pixel();
        }
    }

    set_black_color();
    for (int i = 1; i < width-1; i++) // height
    {
        move_to(posY + i ,posX*2 + 2);
        for (int j = 1; j < width-1; j++) // width
        {
            pixel();
        }
    }

    set_green_color();
    int stemWidth = width%2 == 0?2:1;
    for (int i = 1; i <= height - width; i++) {
        move_to(posY + width + i - 1,posX *2 + width - stemWidth);
        for (int j = 1; j <= stemWidth; j++) {
            pixel();
        }
    }

}

void louka(int columns, int rows) {

    int width = 5;
    int height = 10;

    kvetina(width, height, 1, 1);

    for (int i = 1; i <= columns*width; i += width + 1) {
        for (int j = 1; j <= rows*height; j += height + 1) {
            kvetina(width, height, i, j);
        }
    }

}



void animace() {
    Snake snake = {NULL, 7};
    snake.body = malloc(8*sizeof(Vector2));

    for (int i = 0; i < snake.length; i++) {
        snake.body[i].x = 15+i;
        snake.body[i].y = 15;
    }

    for (int i = 0; i < 1000; i++) {
        showSnake(&snake);
        //showSnakeBodyDebug(&snake);
        moveSnakeRandom(&snake);
        animate_ms((unsigned int)200);
        clear_screen();
    }
}

void moveSnakeRandom(Snake* snake) {

    for (int i = snake->length; i >= 1; i--) {
        snake->body[i] = snake->body[i-1];
    }

    Vector2 newPos = {-1,-1};
    do {
        newPos.x =  snake->body[0].x + (rand()%2 == 1?-1:1);
        newPos.y =  snake->body[0].y + (rand()%2 == 1?-1:1);
    } while (isPosInSnake(snake, newPos) ||
            newPos.x < 2 ||
            newPos.y < 2 ||
            newPos.x > 19 ||
            newPos.y > 19);

    snake->body[0].x = newPos.x;
    snake->body[0].y = newPos.y;
}

void showSnake(Snake* snake) {

    for (int i = 0; i < snake->length; i++) {
        if (i == 0) {
            set_blue_color();
        }else if (i % 2 == 0) {set_green_color();}
        else {set_yellow_color();}

        move_to(snake->body[i].y, snake->body[i].x * 2);
        printf("%d ",i);
    }
}

bool isPosInSnake(Snake* snake, Vector2 newPos) {
    bool isIn = false;
    for (int i = 0; i < snake->length; i++) {
        if (snake->body[i].x == newPos.x && snake->body[i].y == newPos.y) {
            isIn = true;
        }
    }
    return isIn;
}

void showSnakeBodyDebug(Snake* snake) {
    for (int i = 0; i < snake->length; i++) {
        printf("%d.  x = %d   y = %d\n", i,snake->body[i].x,snake->body[i].y);
    }
}


void pixel(){
    draw_pixel();
    move_right();
    draw_pixel();
    move_right();
}

void pixelDebug(){
    printf("x");
    printf("x");
}