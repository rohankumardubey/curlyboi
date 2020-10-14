#include <stddef.h>
#include <stdbool.h>
#include <ncurses.h>

enum Direction { UP, DOWN, LEFT, RIGHT };
enum Status { SUCCESS, FAILURE };

struct Point {
    int x;
    int y;
    wchar_t* data;
    struct Point *next;
};

// typedef struct Point;

struct Board {
    Point* snake;
    Point* foods;
    int xmax;
    int ymax;
};

// typedef struct Board;

Point* create_cell(int x, int y, wchar_t* data);
Point* create_snake();
Board* create_board(Point* foods, Point* snake, int xmax, int ymax);
bool is_same_place(Point* cell1, Point* cell2);
bool list_contains(Point* cell, Point* list);
Point* create_random_cell(int xmax, int ymax, wchar_t* data);
void add_new_food(Board* board);
bool remove_from_list(Point* element, Point** list);
Point* next_move(Board* board, enum Direction dir);
enum Status move_snake(Board* board, enum Direction dir);
