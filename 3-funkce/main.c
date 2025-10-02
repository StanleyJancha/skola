#include "drawing.h"

#include <stdlib.h>

typedef enum {
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_WHITE,
    COLOR_YELLOW
} Color;

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


void pixel();

void prerusovaneCary(Vector2 start, int length);
void schody(StairType stairType, int length);
void vykreslitKvetiny(Object objects[], int count);

int main() {

    clear_screen();

    int drawing = 2;
    //scanf("%d", &drawing);

    switch (drawing) {
        case 0:{
            Vector2 startPos = {1,1};
            prerusovaneCary(startPos,6);

            Vector2 startPos2 = {6,8};
            prerusovaneCary(startPos2, 9);

        }break;
        case 1:{
            schody(STAIR_DOWN, 20);

        }break;
        case 2:{
            Object kvet;
            kvet.position = (Vector2){5, 5};
            kvet.size = (Vector2){6,6};

            Object kvet1;
            kvet1.position = (Vector2){20, 10};
            kvet1.size = (Vector2){9, 9};

            Object *objects = malloc(2*sizeof(Object*));
            objects[0] = kvet;
            objects[1] = kvet1;

            vykreslitKvetiny(objects,2);

        }break;
        case 3:{}break;
        case 4:{}break;
    }
    end_drawing();

    return 0;
}

void prerusovaneCary(Vector2 start, int length) {

    move_to(start.x, start.y);
    set_red_color();
    for (int i = 0; i < length; i++)
    {
        if (i % 2 != 0)
        {
            draw_pixel();
            
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
            draw_pixel();
            move_right();
            move_down();
        }
        

    }break;

    default:
        break;
        printf("stairType je spatne");
    }
}

void vykreslitKvetiny(Object objects[], int count){
    for (int i = 0; i < 1; i++)
    {
        //printf("Pos {%d, %d} Size {%d, %d}\n", objects[i].position.x, objects[i].position.y, objects[i].size.x, objects[i].size.y);
    
        Object curObj = objects[i];

        set_blue_color(); // zakladni tvar
        move_to(curObj.position.y, curObj.position.x*2);
        for (int i = 1; i <= curObj.size.x; i++) // radky
        {
            for (int j = 1; j <= curObj.size.y; j++) // spoupce
            {
                if ( // rohy udela prazdne
                    ((i == 1 && j == 1) || 
                    (i == curObj.size.x && j == 1) || 
                    (i == 1 && j == curObj.size.y) || 
                    (i == curObj.size.x && j == curObj.size.y))
                )
                {
                    reset_color();
                }else{
                    set_blue_color();
                }
                pixel();
            }
            move_to(curObj.position.y+i, curObj.position.x*2); // posunuti na spodnejsi radek
        }

        move_to(curObj.position.y + curObj.size.y/2-curObj.size.y/4, curObj.position.x*2 + curObj.size.x/2-curObj.size.x/4); // vykresleni prostredku
        set_yellow_color();        
        for (int i = 0; i < curObj.size.y/2; i++)
        {
            for (int j = 0; j < curObj.size.x/2; j++)
            {
                pixel();
            }
            move_to(curObj.position.y + curObj.size.y/2-curObj.size.y/4 + i, curObj.position.x*2 + curObj.size.x/2);
        }
        
    
        reset_color();
    }
    
}

void pixel(){
    draw_pixel();
    move_right();
    draw_pixel();
    move_right();
}