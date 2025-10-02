#include "drawing.h"

int main() {
    // Keep this line here
    clear_screen();

    // Load the input - what should be drawn.
    int drawing = 0;
    scanf("%d", &drawing);

    // Put your drawing code here
    set_blue_color();
    draw_pixel();
    move_right();

    set_red_color();
    printf("Hello UPR");

    set_blue_color();
    draw_pixel();

    // Keep this line here
    end_drawing();

    return 0;
}