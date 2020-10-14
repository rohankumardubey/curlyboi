#include <stdlib.h>
#include <ncurses.h>

enum Direction get_next_move(enum Direction previous);
void display_snake(Point* snake, enum Direction dir);
void display_foods(Point* foods);
